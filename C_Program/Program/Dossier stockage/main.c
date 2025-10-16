#include<stdio.h>

void increment_count_file() {
    FILE *file = fopen("count.txt", "r+");
    if (!file) {
        perror("fopen");
        return;
    }

    int count = 0;
    fscanf(file, "%d", &count);
    count++;

    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d\n", count);
    fclose(file);
    printf("Le compteur a été incrémenté. Nouvelle valeur: %d\n", count);
}

int main() {
    increment_count_file();
    return 0;
}
