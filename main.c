#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#define ROWS 10000
#define COLUMNS 10000

int **create_matrix() {
    int i, j;
    int n = 0;
    int **matrix = (int **)malloc(ROWS * sizeof(int *));
    for (i = 0; i < ROWS; i++) {
        matrix[i] = (int *)malloc(COLUMNS * sizeof(int));
    }
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            matrix[i][j] = n;
            n++;
        }
    }
    return matrix;
}

void destroy_matrix(int **matrix) {
    int i;
    for (i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void horizontal_operation(int **matrix) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            matrix[i][j] *= 2;
        }
    }
}

void vertical_operation(int **matrix) {
    int i, j;
    for (j = 0; j < COLUMNS; j++) {
        for (i = 0; i < ROWS; i++) {
            matrix[i][j] *= 2;
        }
    }
}

uint64_t getTime(void) {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return ((uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec));
}

uint64_t horizontal_time() {
    int **m;
    uint64_t start, finish;
    m = create_matrix();
    start = getTime();
    horizontal_operation(m);
    finish = getTime();
    destroy_matrix(m);
    return finish - start;
}

uint64_t vertical_time() {
    int **m;
    uint64_t start, finish;
    m = create_matrix();
    start = getTime();
    vertical_operation(m);
    finish = getTime();
    destroy_matrix(m);
    return finish - start;
}

int main() {
    uint64_t h_time = horizontal_time();
    uint64_t v_time = vertical_time();

    printf("Vertical operation time: \t%lu\n", v_time);
    printf("Horizontal operation time: \t%lu\n", h_time);
    printf("Vertical / Horizontal Ratio: %f\n", (float)v_time / h_time);
    return 0;
}