#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2
#define INCREMENT_COUNT 2

pthread_mutex_t lock;
int shared_counter = 0;

// Define a wrapper struct for pthread_mutex_t *
typedef struct {
    pthread_mutex_t *mutex;
} GuardMutex;

// Function to acquire the mutex
static inline GuardMutex guard_mutex_acquire(pthread_mutex_t *mutex) {
    pthread_mutex_lock(mutex);
    return (GuardMutex){ .mutex = mutex };
}

// Function to release the mutex (used with __attribute__((cleanup)))
static inline void guard_mutex_release(GuardMutex *guard) {
    printf("guard_mutex_release");
    pthread_mutex_unlock(guard->mutex);
}

// Define a macro to use guard for mutex
#define GUARD_MUTEX(m) __attribute__((cleanup(guard_mutex_release))) GuardMutex m = guard_mutex_acquire(&lock)

// Thread function
void *increment_counter(void *arg) {
    int id = *(int *)arg;
    free(arg);

    for (int i = 0; i < INCREMENT_COUNT; i++) {
        GUARD_MUTEX(guard);  // Auto lock/unlock
        shared_counter++;
    }

    printf("Thread %d finished execution.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return EXIT_FAILURE;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int *thread_id = malloc(sizeof(int));
        if (!thread_id) {
            perror("Malloc failed");
            return EXIT_FAILURE;
        }
        *thread_id = i + 1;

        if (pthread_create(&threads[i], NULL, increment_counter, thread_id) != 0) {
            perror("Thread creation failed");
            return EXIT_FAILURE;
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", shared_counter);
    return EXIT_SUCCESS;
}
