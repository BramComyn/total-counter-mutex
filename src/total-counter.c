#include <pthread.h>
#include <stdio.h>

pthread_t thread1, thread2;

const int n = 50000000;
int number;

void* total() {
    for (int count = 0; count < n; count++) 
        number++;
}

int main(void) {
    number = 0;

    pthread_create(&thread1, NULL, total, NULL);
    pthread_create(&thread2, NULL, total, NULL);

    pthread_join(thread1, NULL); pthread_join(thread2, NULL);
    fprintf(stdout, "Total: %d\n", number);

    return 0;
}
