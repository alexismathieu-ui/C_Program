#include<stdio.h>

int main() {
    int factorielle = 5;
    int a , b = 1;

    for (a=1; a <= factorielle; a++)
        b = b*a;
    printf("La factorielle de %d est de : %d\n", factorielle, b);  
    return 0;
}