#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void max(int *number, int size) {
    int max = number[0];
    for (int i = 1; i < size; i++) {
        if (number[i] > max) {
            max = number[i];
        }
    }
    printf("Les nombres dans le tableau sont : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", number[i]);
    }
    printf("\n");
    printf("Le nombre maximum est : %d\n", max);
    
}

int main() {
    int size;
    printf("Entrez la taille du tableau : ");
    scanf("%d", &size);
    int *number = (int *)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        number[i] = rand() % 100; 
    }
    max(number, size);
    free(number);
    return 0;
    
}