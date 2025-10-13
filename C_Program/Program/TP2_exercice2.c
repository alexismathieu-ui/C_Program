#include<stdio.h>

int main() {
    int weight = 1;
    float height = 1;
    float IMC;
    
    printf("Entrez votre poids (kg) : ");
    scanf("%d", &weight);
    
    printf("Entrez votre taille (m) : ");
    scanf("%f", &height);
    
    IMC = weight / (height * height);
    printf("Votre IMC est de : %.2f\n", IMC);
    
    if (IMC < 16.5) {
        printf("Dénutrition\n");
    } 
    
    else if (IMC >= 16.5 && IMC < 18.5) {
        printf("Maigre\n");
    } 
    
    else if (IMC >= 18.5 && IMC < 25) {
        printf("Corpulence normale\n");
    } 
    
    else if (IMC >= 25 && IMC < 30) {
        printf("Surpoids\n");
    } 
    
    else if (IMC >= 30 && IMC < 35) {
        printf("Obésité modérée\n");
    } 
    
    else if (IMC >= 35 && IMC < 40) {
        printf("Obésité sévère\n");
    } 
    
    else if (IMC >= 40) {
        printf("Obésité morbide ou massive\n");
    }
    
    
    return 0;
}