#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LEFT (i + n_philosophers - 1) % n_philosophers
#define RIGHT (i + 1) % n_philosophers

pthread_mutex_t chopsticks_mutex[100];
pthread_t philosophers[100];
pthread_cond_t cond[100];
int n_philosophers;
int eat_time, sleep_time, die_time;

void *philosopher(void *arg)
{
    int i = *((int *)arg);
    int count = 0;
    
    while (1) {
        printf("Philosopher %d is thinking.\n", i);
        usleep(rand() % 500000);

        pthread_mutex_lock(&chopsticks_mutex[LEFT]);
        printf("Philosopher %d has picked up chopstick %d.\n", i, LEFT);

        if (pthread_mutex_trylock(&chopsticks_mutex[RIGHT]) == 0) {
            printf("Philosopher %d has picked up chopstick %d.\n", i, RIGHT);
            
            printf("Philosopher %d is eating.\n", i);
            usleep(rand() % (eat_time * 1000000));
            
            count++;
            if (count == die_time) {
                printf("Philosopher %d has died.\n", i);
                pthread_mutex_unlock(&chopsticks_mutex[LEFT]);
                pthread_mutex_unlock(&chopsticks_mutex[RIGHT]);
                pthread_cond_signal(&cond[LEFT]);
                pthread_cond_signal(&cond[RIGHT]);
                pthread_exit(NULL);
            }
            
            pthread_mutex_unlock(&chopsticks_mutex[LEFT]);
            pthread_mutex_unlock(&chopsticks_mutex[RIGHT]);
            printf("Philosopher %d has finished eating.\n", i);
        } else {
            printf("Philosopher %d could not pick up chopstick %d.\n", i, RIGHT);
            pthread_mutex_unlock(&chopsticks_mutex[LEFT]);
        }
        
        printf("Philosopher %d is sleeping.\n", i);
        usleep(rand() % (sleep_time * 1000000));
    }
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("Usage: %s <n_philosophers> <eat_time> <sleep_time> <die_time>\n", argv[0]);
        return 1;
    }
    
    n_philosophers = atoi(argv[1]);
    eat_time = atoi(argv[2]);
    sleep_time = atoi(argv[3]);
    die_time = atoi(argv[4]);
    
    if (n_philosophers < 2 || n_philosophers > 100 || eat_time < 1 || sleep_time < 1 || die_time < 1) {
        printf("Invalid arguments.\n");
        return 1;
    }

    for (int i = 0; i < n_philosophers; i++) {
        pthread_mutex_init(&chopsticks_mutex[i], NULL);
        pthread_cond_init(&cond[i], NULL);
    }

    for (int i = 0; i < n_philosophers ; i++) {
    int *arg = malloc(sizeof(*arg));
    *arg = i;
    pthread_create(&philosophers[i], NULL, philosopher, arg);
}

for (int i = 0; i < n_philosophers; i++) {
    pthread_join(philosophers[i], NULL);
}

return 0;
}
