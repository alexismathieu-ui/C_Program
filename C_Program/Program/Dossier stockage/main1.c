#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return;
    }

    int lines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
    }

    fclose(file);
    printf("Le fichier '%s' contient %d lignes.\n", filename, lines);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        return 1;
    }

    count_lines(argv[1]);
    return 0;
}