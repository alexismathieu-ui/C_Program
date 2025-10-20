#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <math.h>

//TEST TRI FUSION

void fusion(int arr[], int index1, int index2) {
    int i, j, k;
    int mid = (index1 + index2) / 2;
    
    // TAILLE DES SOUS-TABLEAUX

    int array1 = mid - index1 + 1;
    int array2 = index2 - mid; 

    // CREATIONS DES SOUS-TABLEAUX

    int *l_arr = malloc(array1 * sizeof(int));
    int *r_arr = malloc(array2 * sizeof(int));

    //COPIE DES ELEMENTS DU TABLEAUX PRINCIPAL VERS LES SOUS TABLEAUX

    for (i = 0; i < array1; i++) 
        l_arr[i] = arr[index1 + i];
    for (j = 0; j < array2; j++)
        r_arr[j] = arr[mid + 1 + j];

    i = j = 0;
    k = index1;
    
    // FUSION DES SOUS-TABLEAUX

    while (i < array1 && j < array2) {  
        if (l_arr[i] <= r_arr[j]) arr[k++] = l_arr[i++];
        else arr[k++] = r_arr[j++];
    }

    while (i < array1) arr[k++] = l_arr[i++];
    while (j < array2) arr[k++] = r_arr[j++];

    free(l_arr);
    free(r_arr);
}

// FONCTION TRI FUSION

void struct_tri(int arr[], int index1, int index2) { 
    if (index1 < index2) {
        int mid = (index1 + index2) / 2;
        
        struct_tri(arr, index1, mid);
        struct_tri(arr, mid + 1, index2);
        
        fusion(arr, index1, index2);
    }
}

void tri_fusion(int arr[], int size){
    struct_tri(arr, 0, size -1);
}

int main() {
    srand(time(NULL));
    int number[5];
    number[0] = rand() % 101;
    number[1] = rand() % 101;
    number[2] = rand() % 101;
    number[3] = rand() % 101;
    number[4] = rand() % 101;

    printf("Tableau original : ");
    for (int i = 0; i < 5; i++) printf("%d ", number[i]);
    printf("\n");

    tri_fusion(number, 5);

    printf("Tableau trié : ");
    for (int i = 0; i < 5; i++) printf("%d ", number[i]);
    printf("\n");

    return 0;
}