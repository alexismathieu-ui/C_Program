#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

void swap(int *num1, int *num2) { // Fonction pour échanger deux nombres
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int main() {
    int number1, number2;
    
    printf("Entrez un premier nombre : ");
    scanf("%d", &number1);
    
    printf("Entrez un deuxième nombre : ");
    scanf("%d", &number2);
    
    printf("Avant l'échange : nombre1 = %d, nombre2 = %d\n", number1, number2);
    swap(&number1, &number2);
    
    printf("Après l'échange : nombre1 = %d, nombre2 = %d\n", number1, number2);
    
    return 0;
}