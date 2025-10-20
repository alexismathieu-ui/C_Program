#include<stdio.h>

void function_number_prime(int n) {
    int i;
    int Prime = 1; 

    if (n <= 1) {
        Prime = 0;
    } else {
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                Prime = 0;
                break;
            }
        }
    }

    if (Prime) {
        printf("%d est un nombre premier.\n", n);
    } else {
        printf("%d n'est pas un nombre premier.\n", n);
    }
}

int main () {
    int number;

    printf("Entrez votre nombre si vous voulez vérifier s'il est premier : ");
    scanf("%d", &number);

    function_number_prime(number);
    return 0;
}