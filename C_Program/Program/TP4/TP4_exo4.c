#include<stdio.h>

int main(){
    int table = 1;
    int i = 1;
    int j = 1;
    int following = 0;
    int height = 1;

    printf("Entre jusqu'à où votre tableau de multiplication doit aller : ");
    scanf("%d", &table);
    printf("Voici le tableau de multiplication de %d : \n", table);
    for (i = 1; i <= table; i++){
        for (j = 1; j <= table-1; j++){
            following = i * j;
            printf("%d x %d = %d\n", i, j, following);
        }
        following = table * height;
        printf("%d x %d = %d\n", table, height, following);
        height++;
    }
}