#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void alphabet_dynamic(){ // alloue un tableau de 26 caractères dynamiquement et initialiser les lettre de l'alphabet en minuscules
    char *alphabet = (char *)malloc(26 * sizeof(char));
    if (alphabet == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 'a' + i;
    }
    
    printf("L'alphabet est : ");
    for (int i = 0; i < 26; i++) {
        printf("%c ", alphabet[i]);
    }
    printf("\n");
    
    free(alphabet);
    
}



int main() {
    alphabet_dynamic();
    return 0;
}