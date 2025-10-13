#include<stdio.h>

int main() { 
    int age = 20;
    char sex = 'M';

    if (age == 20 && (sex == 'M' || sex == 'F')) {
        printf("Vous êtes un homme ou une femme de 20 ans.\n");
    }
}