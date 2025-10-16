#include<stdio.h>

int main() {
    int HT = 1;
    float TVA = 1;
    printf("Entrez le prix HT : ");
    scanf("%d", &HT);
    printf("Entrez le prix TVA (0 - 1): ");
    scanf("%f", &TVA);
    
    float TTC = HT * (1 + TVA);
    printf("La TVA est de : %.2f\n", TVA * 100);
    printf("Le prix TTC est de : %.2f\n", TTC);
    return 0;
}