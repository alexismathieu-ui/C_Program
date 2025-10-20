#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
    srand(time(NULL));
    int number[5] = {rand() % 21, rand() % 21, rand() % 21, rand() % 21, rand() % 21};
    float average;

    average = (number[0] + number[1] + number[2] + number[3] + number[4]) / 5.0;
    printf("Les notes sont : %d, %d, %d, %d, %d\n", number[0], number[1], number[2], number[3], number[4]);
    printf("La moyenne est de : %.2f\n", average);
    return 0;
}