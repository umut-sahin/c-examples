#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

void *say_hi(void *data) {
    printf("Hello from the new thread!\n");
    *((int *)data) += 42;

    return data;
}

int main(void) {
    assert(setlocale(LC_MESSAGES, "en_US.UTF-8") != NULL);

    int initial_data = 0;

    pthread_t thread_id;
    int data_to_pass = initial_data;
    int pthread_create_result = pthread_create(&thread_id, NULL, say_hi, &data_to_pass);
    if (pthread_create_result != 0) {
        errno = pthread_create_result;
        fprintf(
            stderr,
            "pthread error: unable to create the new thread (%s)\n",
            strerror(errno)
        );
        exit(EXIT_FAILURE);
    }

    printf("Hello from the main thread!\n");

    void *threads_return;
    pthread_join(thread_id, &threads_return);

    assert((int *)threads_return == &data_to_pass);
    assert(data_to_pass == initial_data + 42);

    return EXIT_SUCCESS;
}
