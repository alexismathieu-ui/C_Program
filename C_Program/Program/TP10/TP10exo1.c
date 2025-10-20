#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


// Fonction pour créer et afficher un tableau 2D

void tableau_2d(int rows, int cols) {
    int **array = malloc(rows * sizeof(*array));

    // Allocation de chaque ligne

    for (int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(*array[i]));
    }
    // Remplissage et affichage du tableau

    int val = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = val++; // Remplir avec des valeurs qui se séquencent
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) free(array[i]);
    free(array);
}

int main(void) {
    tableau_2d(4, 4);
    return 0;
}