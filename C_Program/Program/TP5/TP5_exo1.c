#include<stdio.h>

void function_factorielle(int n) {
    int a , b = 1;
    for (a=1; a <= n; a++)
        
    b = b*a;
    
    printf("La factorielle de %d est : %d\n", n, b);
}


int main() {
    int number;

    printf("Entrez la factorielle de votre choix : ");
    scanf("%d", &number);

    function_factorielle(number);
    return 0;
}