#include<stdio.h>

int main() {
    int rayon = 1;
    float perimetre;
    printf("Entrez le rayon du cercle (m) : ");
    scanf("%d", &rayon);

    perimetre = 2 * 3.14 * rayon;
    printf("Le périmètre du cercle est de : %.2f\n", perimetre);
    return 0;
}