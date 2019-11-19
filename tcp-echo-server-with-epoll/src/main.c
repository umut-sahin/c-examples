#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <unistd.h>

int main(void) {
    assert(setlocale(LC_MESSAGES, "en_US.UTF-8") != NULL);

    sigset_t signals_to_capture;
    sigfillset(&signals_to_capture);
    sigprocmask(SIG_SETMASK, &signals_to_capture, NULL);

    int signal_fd = signalfd(-1, &signals_to_capture, 0);
    if (signal_fd == -1) {
        fprintf(
            stderr,
            "io error: unable to create the signal file descriptor (%s)\n",
            strerror(errno)
        );
        goto SIGNALFD_FAILED;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        fprintf(
            stderr,
            "io error: unable to create the epoll instance (%s)\n",
            strerror(errno)
        );
        goto EPOLL_CREATE_FAILED;
    }

    struct epoll_event signal_fd_event;
    memset(&signal_fd_event, 0, sizeof(struct epoll_event));
    signal_fd_event.events = EPOLLIN;
    signal_fd_event.data.fd = signal_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, signal_fd, &signal_fd_event) == -1) {
        fprintf(
            stderr,
            "epoll error: unable to add the signal file descriptor to the epoll instances interest list (%s)\n",
            strerror(errno)
        );
        goto EPOLL_CTL_ADD_SIGNAL_FAILED;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (server_fd == -1) {
        fprintf(
            stderr,
            "io error: unable to create the server socket (%s)\n",
            strerror(errno)
        );
        goto SOCKET_FAILED;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8000);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in)) == -1) {
        fprintf(
            stderr,
            "address binding error: unable to bind the address to the server socket (%s)\n",
            strerror(errno)
        );
        goto BIND_FAILED;
    }

    if (listen(server_fd, 128) == -1) {
        fprintf(
            stderr,
            "listening error: unable to start listening on the server socket (%s)\n",
            strerror(errno)
        );
        goto LISTEN_FAILED;
    }

    struct epoll_event server_fd_event;
    memset(&server_fd_event, 0, sizeof(struct epoll_event));
    server_fd_event.events = EPOLLIN;
    server_fd_event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &server_fd_event) == -1) {
        fprintf(
            stderr,
            "epoll error: unable to add the server socket to the epoll instances interest list (%s)\n",
            strerror(errno)
        );
        goto EPOLL_CTL_ADD_SERVER_FAILED;
    }

    bool terminated = false;
    while (!terminated) {
        struct epoll_event events[128];
        int available_event_count = epoll_wait(epoll_fd, events, 128, -1);
        for (int i = 0; i < available_event_count; i++) {
            if (events[i].data.fd == signal_fd) {
                struct signalfd_siginfo caught_signal;
                ssize_t read_bytes = read(
                    signal_fd,
                    &caught_signal,
                    sizeof(struct signalfd_siginfo)
                );
                if (read_bytes == -1) {
                    fprintf(
                        stderr,
                        "io warning: unable to read the next signal from the signal file descriptor (%s)\n",
                        strerror(errno)
                    );
                    continue;
                }

                switch (caught_signal.ssi_signo) {
                    case SIGINT:
                    case SIGTERM: {
                        terminated = true;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            else if (events[i].data.fd == server_fd) {
                while (true) {
                    int client_fd = accept(server_fd, NULL, NULL);
                    if (client_fd == -1) {
                        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                            fprintf(
                                stderr,
                                "io warning: unable to accept a client (%s)\n",
                                strerror(errno)
                            );
                            continue;
                        }
                        else {
                            break;
                        }
                    }

                    struct epoll_event client_fd_event;
                    memset(&client_fd_event, 0, sizeof(struct epoll_event));
                    client_fd_event.events = EPOLLIN | EPOLLRDHUP;
                    client_fd_event.data.fd = client_fd;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_fd_event) == -1) {
                        close(client_fd);
                        continue;
                    }
                }
            }
            else {
                if (events[i].events & EPOLLRDHUP) {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    close(events[i].data.fd);
                }
                else {
                    char buffer[8192];
                    ssize_t received_bytes = recv(events[i].data.fd, buffer, 8192, 0);
                    if (received_bytes == -1) {
                        fprintf(
                            stderr,
                            "io warning: unable to read a clients input (%s)\n",
                            strerror(errno)
                        );
                        continue;
                    }

                    send(
                        events[i].data.fd,
                        buffer,
                        (size_t)received_bytes,
                        MSG_NOSIGNAL
                    );
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    close(signal_fd);
    return EXIT_SUCCESS;

    EPOLL_CTL_ADD_SERVER_FAILED:

    LISTEN_FAILED:

    BIND_FAILED:
    close(server_fd);

    SOCKET_FAILED:

    EPOLL_CTL_ADD_SIGNAL_FAILED:
    close(epoll_fd);

    EPOLL_CREATE_FAILED:
    close(signal_fd);

    SIGNALFD_FAILED:

    return EXIT_FAILURE;
}
