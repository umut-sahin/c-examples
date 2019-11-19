#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/epoll.h>
#include <sys/ioctl.h>
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

    bool terminate = false;
    while (!terminate) {
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
                        terminate = true;
                        printf("Caught termination signal...\n");
                        break;
                    }
                    case SIGWINCH: {
                        struct winsize new_terminal_size;
                        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &new_terminal_size) == -1) {
                            fprintf(
                                stderr,
                                "io warning: unable to get the new terminal size (%s)\n",
                                strerror(errno)
                            );
                            break;
                        }

                        printf(
                            "Caught resize signal (Now have %d rows and %d columns)...\n",
                            new_terminal_size.ws_row,
                            new_terminal_size.ws_col
                        );
                        break;
                    }
                    default: {
                        printf("Caught another signal (%u)\n", caught_signal.ssi_signo);
                        break;
                    }
                }
            }
        }
    }

    close(epoll_fd);
    close(signal_fd);
    return EXIT_SUCCESS;

    EPOLL_CTL_ADD_SIGNAL_FAILED:
    close(epoll_fd);

    EPOLL_CREATE_FAILED:
    close(signal_fd);

    SIGNALFD_FAILED:

    return EXIT_FAILURE;
}
