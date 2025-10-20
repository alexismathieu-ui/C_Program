#include<stdio.h>

int main(){
    int numbers[10] = { 4, 5, 1, 10, 32, 0, 9, 14, 23, 2};
    int i = 1;
    for (i = 1;i < 10; i++){
        if (numbers[0] < numbers[i]){
            numbers[0] = numbers[i];
        }
    }
    printf("Le nombre le plus grand est : %d\n", numbers[0]);
}