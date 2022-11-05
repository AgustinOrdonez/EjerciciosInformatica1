#include <pthread.h>

void *work(void *);

pthread_mutex_t mutex;

int main() {
    pthread_t threadId;
    int value;
    int *value1;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threadId, NULL, work, &value);
    pthread_join(threadId, (void **) &value1);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void *work(void *arg) {
    int a;
    pthread_mutex_lock(&mutex);
    int *value = &a;
    pthread_mutex_unlock(&mutex);

    return value;
}