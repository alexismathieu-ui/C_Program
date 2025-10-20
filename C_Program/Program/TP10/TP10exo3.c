#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int parse_N(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <taille N>\n", argv[0]);
        return -1;
    }
    int N = atoi(argv[1]);
    if (N <= 0) {
        printf("Erreur : N doit être un entier positif.\n");
        return -1;
    }
    return N;
}

int **alloc_table(int N) {
    int **table = malloc(N * sizeof(int *));
    if (!table) { printf("Erreur Allocation mémoire (1)\n"); return NULL; }
    for (int i = 0; i < N; i++) {
        table[i] = malloc(N * sizeof(int));
        if (!table[i]) {
            printf("Erreur Allocation mémoire (2)\n");
            for (int j = 0; j < i; j++) free(table[j]);
            free(table);
            return NULL;
        }
    }
    return table;
}

void fill_table(int **table, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            table[i][j] = (i + 1) * (j + 1);
}

void print_table(int **table, int N) {
    printf("Table de multiplication %dx%d :\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%4d ", table[i][j]);
        printf("\n");
    }
}

void free_table(int **table, int N) {
    for (int i = 0; i < N; i++) free(table[i]);
    free(table);
}

int main(int argc, char *argv[]) {
    int N = parse_N(argc, argv);
    if (N < 0) return 1;
    int **table = alloc_table(N);
    if (!table) return 1;
    fill_table(table, N);
    print_table(table, N);
    free_table(table, N);
    return 0;
}
