#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


/* Remplacez entièrement le contenu précédent par ce bloc (fichier main.c) */
/* Programme : lit un fichier PPM (P6) passé en argument et écrit greyscale.ppm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

static void skip_spaces_and_comments(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) continue;
        if (c == '#') {
            /* skip rest of line */
            while ((c = fgetc(f)) != EOF && c != '\n') {}
            continue;
        }
        ungetc(c, f);
        break;
    }
}

/* Read P6 header: magic, width, height, maxval. Returns 1 on success. */
static int read_ppm_header(FILE *f, int *width, int *height, int *maxval)
{
    char magic[3] = {0};

    if (fread(magic, 1, 2, f) != 2) return 0;
    magic[2] = '\0';
    if (strcmp(magic, "P6") != 0) return 0;

    skip_spaces_and_comments(f);
    if (fscanf(f, "%d", width) != 1) return 0;

    skip_spaces_and_comments(f);
    if (fscanf(f, "%d", height) != 1) return 0;

    skip_spaces_and_comments(f);
    if (fscanf(f, "%d", maxval) != 1) return 0;

    /* consume single whitespace (the one after maxval) to reach binary data */
    int c = fgetc(f);
    if (c == '\r') {
        /* handle possible CRLF */
        int c2 = fgetc(f);
        if (c2 != '\n') ungetc(c2, f);
    } else if (c != '\n' && !isspace(c)) {
        ungetc(c, f);
    }
    return 1;
}

/* Convert input P6 ppm to greyscale P6 written to outpath. Returns 0 on error. */
static int convert_to_greyscale(const char *inpath, const char *outpath)
{
    FILE *fin = fopen(inpath, "rb");
    if (!fin) {
        fprintf(stderr, "Erreur fopen(%s): %s\n", inpath, strerror(errno));
        return 0;
    }

    int width = 0, height = 0, maxval = 0;
    if (!read_ppm_header(fin, &width, &height, &maxval)) {
        fprintf(stderr, "Fichier %s n'est pas un P6 PPM valide ou en-tête invalide\n", inpath);
        fclose(fin);
        return 0;
    }
    if (maxval <= 0 || maxval > 255) {
        fprintf(stderr, "maxval non supporté: %d (seul 1..255 pris en charge)\n", maxval);
        fclose(fin);
        return 0;
    }

    size_t pixels = (size_t)width * (size_t)height;
    size_t data_size = pixels * 3;
    unsigned char *data = (unsigned char *)malloc(data_size);
    if (!data) {
        fprintf(stderr, "malloc échoué\n");
        fclose(fin);
        return 0;
    }

    size_t read = fread(data, 1, data_size, fin);
    fclose(fin);
    if (read != data_size) {
        fprintf(stderr, "Lecture des pixels échouée (%zu/%zu)\n", read, data_size);
        free(data);
        return 0;
    }

    /* Convertir en niveaux de gris (luminance) */
    for (size_t i = 0; i < data_size; i += 3) {
        unsigned char r = data[i];
        unsigned char g = data[i + 1];
        unsigned char b = data[i + 2];
        /* formule de luminance perceptuelle */
        double gray_d = 0.299 * r + 0.587 * g + 0.114 * b;
        int gray = (int)round(gray_d);
        if (gray < 0) gray = 0;
        if (gray > maxval) gray = maxval;
        unsigned char gch = (unsigned char)gray;
        data[i] = data[i + 1] = data[i + 2] = gch;
    }

    FILE *fout = fopen(outpath, "wb");
    if (!fout) {
        fprintf(stderr, "Erreur fopen(%s): %s\n", outpath, strerror(errno));
        free(data);
        return 0;
    }

    /* Écrire en-tête P6 */
    if (fprintf(fout, "P6\n%d %d\n%d\n", width, height, maxval) < 0) {
        fprintf(stderr, "Erreur écriture en-tête\n");
        free(data);
        fclose(fout);
        return 0;
    }

    size_t written = fwrite(data, 1, data_size, fout);
    free(data);
    fclose(fout);
    if (written != data_size) {
        fprintf(stderr, "Erreur fwrite (%zu/%zu)\n", written, data_size);
        return 0;
    }

    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input.ppm>\n", argc ? argv[0] : "convert_ppm");
        return 1;
    }

    const char *input = argv[1];
    const char *output = "greyscale.ppm";

    if (convert_to_greyscale(input, output)) {
        printf("Conversion réussie : %s -> %s\n", input, output);
        return 0;
    } else {
        fprintf(stderr, "Échec de la conversion\n");
        return 2;
    }
}

