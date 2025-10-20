#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

// Fonction pour créer et afficher un tableau 2D
void tableau_2d(int rows, int cols) {
    int **array = malloc(rows * sizeof *array);
    if (!array) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    // Allocation de chaque ligne
    for (int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof *array[i]);
        if (!array[i]) {
            perror("malloc");
            
            // Libération en cas d'erreur
            for (int k = 0; k < i; k++) free(array[k]);
            free(array);
            exit(EXIT_FAILURE);
        }
    }

    // Remplissage et affichage du tableau
    int val = 1;
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = val++; // Remplir avec des valeurs qui se séquencent
            sum += array[i][j];
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }

    printf("Somme du tableau : %d\n", sum);

    for (int i = 0; i < rows; i++) free(array[i]);
    free(array);
}

int main(void) {
    tableau_2d(4, 4);
    return 0;
}