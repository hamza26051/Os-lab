#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 10

int arr[SIZE];

void *sort_first_half(void *arg) {
    qsort(arr, SIZE / 2, sizeof(int), (__compar_fn_t) &strcmp);
    pthread_exit(NULL);
}

void *sort_second_half(void *arg) {
    qsort(arr + SIZE / 2, SIZE / 2, sizeof(int), (__compar_fn_t) &strcmp);
    pthread_exit(NULL);
}

void merge() {
    int temp[SIZE], i = 0, j = SIZE / 2, k = 0;

    while (i < SIZE / 2 && j < SIZE) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i < SIZE / 2) temp[k++] = arr[i++];
    while (j < SIZE) temp[k++] = arr[j++];

    for (int i = 0; i < SIZE; i++) arr[i] = temp[i];
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    pthread_t t1, t2;

    for (int i = 0; i < SIZE; i++) arr[i] = rand() % 100;

    printf("Original array: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    pthread_create(&t1, NULL, sort_first_half, NULL);
    pthread_create(&t2, NULL, sort_second_half, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    merge();

    printf("Sorted array:   ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
