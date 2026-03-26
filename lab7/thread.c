#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT 10000
#define THREADS 12

long long int i = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg)
{
    int ret;

    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(i >= MAX_COUNT)
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        i++;
        printf("i = %lld\n", i);
        pthread_mutex_unlock(&mutex);

    }
}

int main(void)
{
    int j;
    int ret;
    pthread_t threads[THREADS];

    for(j = 0; j < THREADS; j++)
    {
        ret = pthread_create(&threads[j], NULL, count, NULL);

        if(ret != 0)
        {
            fprintf(stderr, "pthread_create failed for thread %d (error %s)", j, strerror(ret));
        }
    }
}