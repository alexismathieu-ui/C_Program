#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void array_concat(int *array1, int size1, int *array2, int size2, int *result) {
    for (int i = 0; i < size1; i++) {
        result[i] = array1[i];
    }
    for (int j = 0; j < size2; j++) {
        result[size1 + j] = array2[j];
    }
    
    printf("Le tableau concaténé est : ");
    for (int k = 0; k < size1 + size2; k++) {
        printf("%d ", result[k]);
    }
    printf("\n");
}

int main(){
    int size1 = 1; 
    int size2 = 1;
    
    printf("Entrez la taille du premier tableau : ");
    scanf("%d", &size1);
    int *array1 = (int *)malloc(size1 * sizeof(int));
    
    printf("Entrez les éléments du premier tableau : ");
    for (int i = 0; i < size1; i++) {
        scanf("%d", &array1[i]);
    }
    
    printf("Entrez la taille du deuxième tableau : ");
    scanf("%d", &size2);
    
    int *array2 = (int *)malloc(size2 * sizeof(int));
    
    printf("Entrez les éléments du deuxième tableau : ");
    for (int j = 0; j < size2; j++) {
        scanf("%d", &array2[j]);
    }
    
    int *result = (int *)malloc((size1 + size2) * sizeof(int));
    
    array_concat(array1, size1, array2, size2, result);
    
    free(array1);
    free(array2);
    free(result);
    
    return 0;

}