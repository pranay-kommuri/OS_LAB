#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MAX_MEALS 3
#define THINK_TIME 2
#define EAT_TIME 2

enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];

pthread_mutex_t mutex;

sem_t s[NUM_PHILOSOPHERS];

int meals_eaten[NUM_PHILOSOPHERS] = {0};

int total_meals_eaten = 0;

const char* names[NUM_PHILOSOPHERS] = {
    "Socrates", "Plato", "Aristotle", "Descartes", "Kant"
};

void print_state() {
    printf("\nPhilosophers' States: ");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        printf("%s: ", names[i]);
        switch (state[i]) {
            case THINKING: printf("THINKING "); break;
            case HUNGRY:   printf("HUNGRY   "); break;
            case EATING:   printf("EATING   "); break;
        }
    }
    printf("\n");

    printf("Forks: ");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (state[i] == EATING) {
            printf("Fork %d: Used by %s | ", i, names[i]);
            printf("Fork %d: Used by %s | ", (i + 1) % NUM_PHILOSOPHERS, names[i]);
        }
    }
    printf("\n");

    printf("Meals eaten: ");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        printf("%s: %d | ", names[i], meals_eaten[i]);
    }
    printf("Total: %d\n", total_meals_eaten);
}

void test(int phil_id) {
    int left = (phil_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (phil_id + 1) % NUM_PHILOSOPHERS;

    if (state[phil_id] == HUNGRY &&
        state[left] != EATING &&
        state[right] != EATING) {
        state[phil_id] = EATING;
        printf("%s starts eating (meal #%d)\n", names[phil_id], meals_eaten[phil_id] + 1);

        sem_post(&s[phil_id]);
    }
}

void take_forks(int phil_id) {
    pthread_mutex_lock(&mutex);

    state[phil_id] = HUNGRY;
    printf("%s is hungry\n", names[phil_id]);
    print_state();

    test(phil_id);

    pthread_mutex_unlock(&mutex);

    sem_wait(&s[phil_id]);
}

void put_forks(int phil_id) {
    pthread_mutex_lock(&mutex);

    state[phil_id] = THINKING;

    meals_eaten[phil_id]++;
    total_meals_eaten++;

    printf("%s finished eating and is thinking again (completed %d meals)\n",
           names[phil_id], meals_eaten[phil_id]);
    print_state();

    int left = (phil_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (phil_id + 1) % NUM_PHILOSOPHERS;

    test(left);
    test(right);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* arg) {
    int phil_id = *(int*)arg;

    printf("%s has joined the table\n", names[phil_id]);

    while (meals_eaten[phil_id] < MAX_MEALS) {
        printf("%s is thinking\n", names[phil_id]);
        sleep(rand() % THINK_TIME + 1);

        take_forks(phil_id);

        printf("%s is eating\n", names[phil_id]);
        sleep(rand() % EAT_TIME + 1);

        put_forks(phil_id);
    }

    printf("%s is leaving the table (finished all %d meals)\n", names[phil_id], MAX_MEALS);
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&s[i], 0, 0);
        state[i] = THINKING;
    }

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int phil_ids[NUM_PHILOSOPHERS];

    printf("Dining Philosophers Problem Simulation\n");
    printf("Number of philosophers: %d\n", NUM_PHILOSOPHERS);
    printf("Meals per philosopher: %d\n\n", MAX_MEALS);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        phil_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &phil_ids[i]);
        usleep(100000);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&s[i]);
    }

    printf("\nSimulation complete. All philosophers have finished their meals.\n");
    printf("Total meals eaten: %d\n", total_meals_eaten);

    return 0;
}
