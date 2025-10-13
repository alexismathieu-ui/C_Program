#include<stdio.h>

int main() {
    int hours = 1;
    int days = 1;
    int month = 1;

    printf("Entrez une heure (0-23) : ");
    scanf("%d", &hours);
    
    printf("Entrez un jour de la semaine (0-6) : ");
    scanf("%d", &days);
    
    printf("Entrez un mois (0-11) : ");
    scanf("%d", &month);
    
    // Conditions :

    //Moment de la journée
    if (hours >=6 && hours <=12) { 
        printf("C'est un Matin\n");
    } 
    
    else if (hours >12 && hours <=19) {
        printf("C'est un Après-midi\n");
    } 
    
    else if (hours >=20 && hours <=23) {
        printf("C'est un Soir\n");
    }
    
    else if (hours >=0 && hours < 6) {
        printf("C'est une nuit\n");
    }
    
    else {
        printf("Heure invalide, Veuillez recommencez\n");
    }
    
    //Saison de l'année
    if (month >= 5 && month <= 7) {
        printf("En été\n");
    } 
    
    else if (month >= 3 && month <= 4) {
        printf("Au printemps\n");
    } 
    
    else if (month >= 8 && month <= 10) {
        printf("En automne\n");
    } 
    
    else if (month == 11 || month >= 0 && month <= 2) {
        printf("En hiver\n");
    }
    
    else {
        printf("Mois invalide, Veuillez recommencez\n");
    }
    
    //Semaine ou Week-end
    if (days >=1 && days <=5) {
        printf("\n");
    } 
    
    else if (days >=6 && days <=7) {
        printf("Lors d'un Week-end\n");
    }
    
    else {
        printf("Jour de la semaine invalide, Veuillez recommencez\n");
    }
    
    return 0;
}