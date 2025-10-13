#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
    srand(time(NULL));
    int randomNumber = rand() % 1001;
    int usernumber =1;
    int attempts = 1;
    printf("Bienvenue dans le jeu du juste prix !\n");
    
    while (usernumber != randomNumber) {
        printf("Entrez un nombre entre 0 et 1000 : ");
        scanf("%d", &usernumber);
        
        if (usernumber < randomNumber) {
            printf("C'est plus !\n");
        } 
        else if (usernumber > randomNumber) {
            printf("C'est moins !\n");
        } 
        else if (usernumber == '*'){
            printf("Ressayer !\n");
        }
        attempts++;
    }
    printf("Félicitations ! Vous avez trouvé le juste prix %d en %d tentatives.\n", randomNumber, attempts);
    return 0;
}