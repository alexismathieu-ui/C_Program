#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <math.h>

//TEST TRI FUSION

void fusion(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) //Copie des élément du tableau principal vers les sous tableaux
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = j = 0;
    k = l;
    
    while (i < n1 && j < n2) {  // Fusion des deux sous-tableaux
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void tri_fusion(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        tri_fusion(arr, l, m);
        tri_fusion(arr, m + 1, r);
        fusion(arr, l, m, r);
    }
}

int main() {
    srand(time(NULL));
    int number[5] = {rand() % 101, rand() % 101, rand() % 101, rand() % 101, rand() % 101};

    printf("Tableau original : ");
    for (int i = 0; i < 5; i++) printf("%d ", number[i]);
    printf("\n");

    tri_fusion(number, 0, 4);

    printf("Tableau trié : ");
    for (int i = 0; i < 5; i++) printf("%d ", number[i]);
    printf("\n");

    return 0;
}