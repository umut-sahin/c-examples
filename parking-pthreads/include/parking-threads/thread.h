#ifndef PARKING_THREADS_THREAD
#define PARKING_THREADS_THREAD

typedef struct thread {
    pthread_mutex_t lock;
    pthread_cond_t condvar;
} thread;

#endif
