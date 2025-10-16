#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void my_strlen(const char *str) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

int main(){
    char input[100];
    printf("Entrez une chaîne de caractères : ");
    fgets(input, sizeof(input), stdin); // Lis la chaîne de caractères avec les espaces
    int length = my_strlen(input);
    printf("La longueur de la chaîne est : %d\n", length);
    return 0;
}