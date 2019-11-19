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
#include <unistd.h>

volatile sig_atomic_t terminate = false;

void terminate_server(int signal) {
    (void)(signal);
    terminate = true;
}

int main(void) {
    assert(setlocale(LC_MESSAGES, "en_US.UTF-8") != NULL);

    struct sigaction on_termination_signal = {
        .sa_handler = terminate_server,
        .sa_flags = 0,
    };
    sigaction(SIGTERM, &on_termination_signal, NULL);
    sigaction(SIGINT, &on_termination_signal, NULL);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
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
    server_address.sin_port = htons(8080);
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

    while (!terminate) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            if (errno != EINTR) {
                fprintf(
                    stderr,
                    "io warning: unable to accept a client (%s)\n",
                    strerror(errno)
                );
            }
            continue;
        }

        char request[8192];
        recv(client_fd, request, 8192, 0);

        send(
            client_fd,

            "HTTP/1.1 200 OK\n"
            "Content-Type: text/plain\n"
            "Connection: keep-alive\n\n"

            "Hello World!\n",

            78,

            MSG_NOSIGNAL
        );

        close(client_fd);
    }

    close(server_fd);
    return EXIT_SUCCESS;


    LISTEN_FAILED:

    BIND_FAILED:
    close(server_fd);

    SOCKET_FAILED:

    return EXIT_FAILURE;
}
