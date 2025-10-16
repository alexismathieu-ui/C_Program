#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* Fonctions utilitaires pour générer l'image */
static void hsv_to_rgb(double h, double s, double v,
                       unsigned char *r, unsigned char *g, unsigned char *b)
{
    double c = v * s;
    double hp = fmod(h, 360.0) / 60.0;
    double x = c * (1.0 - fabs(fmod(hp, 2.0) - 1.0));
    double r1 = 0.0, g1 = 0.0, b1 = 0.0;

    if (0.0 <= hp && hp < 1.0)      { r1 = c; g1 = x; b1 = 0.0; }
    else if (1.0 <= hp && hp < 2.0) { r1 = x; g1 = c; b1 = 0.0; }
    else if (2.0 <= hp && hp < 3.0) { r1 = 0.0; g1 = c; b1 = x; }
    else if (3.0 <= hp && hp < 4.0) { r1 = 0.0; g1 = x; b1 = c; }
    else if (4.0 <= hp && hp < 5.0) { r1 = x; g1 = 0.0; b1 = c; }
    else                            { r1 = c; g1 = 0.0; b1 = x; }

    double m = v - c;
    *r = (unsigned char)round((r1 + m) * 255.0);
    *g = (unsigned char)round((g1 + m) * 255.0);
    *b = (unsigned char)round((b1 + m) * 255.0);
}

static int write_ppm_header(FILE *f, int width, int height)
{
    return fprintf(f, "P6\n%d %d\n255\n", width, height) > 0;
}

static int create_image_file(const char *filename, int width, int height)
{
    FILE *f = fopen(filename, "wb");
    if (!f) { perror("fopen"); return 0; }

    if (!write_ppm_header(f, width, height)) {
        fclose(f);
        return 0;
    }

    /* Buffer pour une ligne (plus efficace que fwrite pixel par pixel) */
    size_t row_bytes = (size_t)width * 3;
    unsigned char *row = (unsigned char *)malloc(row_bytes);
    if (!row) { fclose(f); perror("malloc"); return 0; }

    for (int y = 0; y < height; ++y) {
        double v = 1.0 - 0.6 * ((double)y / (height - 1)); /* luminosité décroissante */
        double s = 1.0;

        for (int x = 0; x < width; ++x) {
            double h = ((double)x / (width - 1)) * 360.0;
            unsigned char r, g, b;
            hsv_to_rgb(h, s, v, &r, &g, &b);
            size_t i = (size_t)x * 3;
            row[i] = r;
            row[i + 1] = g;
            row[i + 2] = b;
        }

        if (fwrite(row, 1, row_bytes, f) != row_bytes) {
            free(row);
            fclose(f);
            perror("fwrite");
            return 0;
        }
    }

    free(row);
    fclose(f);
    return 1;
}

void image_creator() {
    const char *filename = "image.ppm";
    int width = 800, height = 200;
    if (create_image_file(filename, width, height))
        printf("Image créée avec succès : %s\n", filename);
    else
        fprintf(stderr, "Échec de la création de l'image\n");
}
int main() {
    image_creator();
    return 0;
}
