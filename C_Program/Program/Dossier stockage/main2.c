#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

void file_number_of_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return;
    }

    int words = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char *token = strtok(buffer, " \t\n");
        while (token) {
            words++;
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
    printf("Le fichier '%s' contient %d mots.\n", filename, words);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        return 1;
    }

    file_number_of_words(argv[1]);
    return 0;
}