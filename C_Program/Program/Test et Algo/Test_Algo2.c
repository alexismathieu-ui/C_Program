#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <math.h>

//TEST TRI A BULLE

void tri(int number[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (number[j] > number[j + 1]) {
                temp = number[j];
                number[j] = number[j + 1];
                number[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int number[5] = {rand() % 101, rand() % 101, rand() % 101, rand() % 101, rand() % 101};
    
    printf("Tableau original : ");
    for (int i = 0; i < 5; i++)
        printf("%d ", number[i]);
    printf("\n");

    tri(number, 5);
    printf("Tableau trié : ");
    for (int i = 0; i < 5; i++)
        printf("%d ", number[i]);
    printf("\n");

    return 0;
}
