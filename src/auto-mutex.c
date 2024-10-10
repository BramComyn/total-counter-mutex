#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int num_cars = 10;
const char directions[3][2] = { {'o', 'n'}, {'n', 'w'}, {'o', 'w'} };

pthread_mutex_t on_lock, nw_lock;

typedef struct car_args {
    const char from;
    const char to;
    int license_plate_number;
} car_args;

void cross_over(const char from, const char to, const int license_plate_number) {
    fprintf(stdout, "Car %d is crossing over from %c to %c\n", license_plate_number, from, to);
}

void in(const char from, const char to) {
    if (from == 'o') {
        if (to == 'w') {
            pthread_mutex_lock(&on_lock);
            pthread_mutex_lock(&nw_lock);
        }
        if (to == 'n') {
            pthread_mutex_lock(&on_lock);
        }
    }

    if (from == 'n' && to == 'w') {
        pthread_mutex_lock(&nw_lock);
    }
}

void out(const char from, const char to) {
    if (from == 'o') {
        if (to == 'w') {
            pthread_mutex_unlock(&nw_lock);
            pthread_mutex_unlock(&on_lock);
        }

        if (to == 'n') {
            pthread_mutex_unlock(&on_lock);
        }
    }

    if (from == 'n' && to == 'w') {
        pthread_mutex_unlock(&nw_lock);
    }
}

void* car(void* arg) {
    car_args* args = (car_args*) arg;

    in(args->from, args->to);
    cross_over(args->from, args->to, args->license_plate_number);
    out(args->from, args->to);

    return NULL;
}

int main(void) {
    srand(time(NULL));

    pthread_mutex_init(&on_lock, NULL);
    pthread_mutex_init(&nw_lock, NULL);

    pthread_t cars[num_cars];

    for (int i = 0; i < num_cars; i++) {
        int random_index = rand() % 3;

        car_args args = {
            directions[random_index][0],
            directions[random_index][1],
            i
        };

        pthread_create(&cars[i], NULL, car, (void*) &args);
    }

    for (int i = 0; i < num_cars; i++) {
        pthread_join(cars[i], NULL);
    }

    pthread_mutex_destroy(&on_lock);
    pthread_mutex_destroy(&nw_lock);

    return 0;
}
