#include<stdio.h>

int main() {
    int number1 = 1;
    int number2 = 1;
    char operation;
    float result;

    printf("Entrez un premier nombre : ");
    scanf("%d", &number1); 
    
    printf("Entrez un deuxième nombre : ");
    scanf("%d", &number2);
    
    printf("Entrez l'opération de votre choix(+, -, *, /) : ");
    scanf(" %c", &operation);

    if (operation == '+') {
        result = number1 + number2;
        printf("Le résultat de %d + %d est de : %.2f\n", number1, number2, result);
    } 
    
    else if (operation == '-') {
        result = number1 - number2;
        printf("Le résultat de %d - %d est de : %.2f\n", number1, number2, result);
    } 
    
    else if (operation == '*') {
        result = number1 * number2;
        printf("Le résultat de %d * %d est de : %.2f\n", number1, number2, result);
    } 
    
    else if (operation == '/') {
        if (number2 != 0) {
            result = (float)number1 / number2;
            printf("Le résultat de %d / %d est de : %.2f\n", number1, number2, result);
        } 
        else {
            printf("Erreur : Division par zéro n'est pas possible.\n");
        }
    } 
    
    else {
        printf("Opération invalide, Veuillez recommencez\n");
    }
}