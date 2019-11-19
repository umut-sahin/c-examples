#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <parking-threads/thread.h>

void *park(void *thread_data) {
    thread *self = thread_data;

    printf("New thread is starting...\n");

    printf("New thread is parking...\n");
    pthread_mutex_lock(&self->lock);
    pthread_cond_wait(&self->condvar, &self->lock);
    pthread_mutex_unlock(&self->lock);
    printf("New thread is unparked...\n");

    printf("New thread is ending...\n");

    pthread_mutex_destroy(&self->lock);
    pthread_cond_destroy(&self->condvar);
    return NULL;
}

int main(void) {
    assert(setlocale(LC_MESSAGES, "en_US.UTF-8") != NULL);

    printf("Main thread is starting...\n");

    pthread_t thread_id;
    thread thread_data = {
        .lock = PTHREAD_MUTEX_INITIALIZER,
        .condvar = PTHREAD_COND_INITIALIZER,
    };
    int pthread_create_result = pthread_create(&thread_id, NULL, park, &thread_data);
    if (pthread_create_result != 0) {
        errno = pthread_create_result;
        fprintf(
            stderr,
            "pthread error: unable to create the new thread (%s)\n",
            strerror(errno)
        );
        exit(EXIT_FAILURE);
    }

    printf("Main thread is going to sleep for 1 seconds...\n");
    sleep(1);
    printf("Main thread is awaken...\n");

    printf("Main thread is unparking the new thread...\n");
    pthread_cond_signal(&thread_data.condvar);

    printf("Main thread is waiting for the new thread...\n");
    pthread_join(thread_id, NULL);

    printf("Main thread is ending...\n");

    return EXIT_SUCCESS;
}
