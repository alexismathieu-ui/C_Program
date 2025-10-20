#include<stdio.h>

int main() {
    
    int factorielle = 1;
    int a , b = 1;

    printf("Entrez la factorielle de votre choix : ");
    scanf("%d", &factorielle);

    for (a=1; a <= factorielle; a++)
        
    b = b*a;
    
    printf("La factorielle de %d est : %d\n", factorielle, b);
}