#include<stdio.h>

void function_palindrome(char str[]) {
    int left = 0;
    int right = 0;

    while (str[right] != '\0') {
        right++;
    }
    right--; 

    while (left < right) {
        if (str[left] != str[right]) {
            printf("La chaîne n'est pas un palindrome.\n");
            return;
        }
        left++;
        right--;
    }
    printf("La chaîne est un palindrome.\n");
}

int main (){
    
    char str[100];

    printf("Entrez une chaîne de caractères : ");
    scanf("%s", str);

    function_palindrome(str);
    return 0;
}