#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

struct Point {
    float x;
    float y;
};

struct Vector2D {
    struct Point origine;
    struct Point destination;
};

// Fonction qui retourne le point milieu d’un vecteur
struct Point get_middle_point(struct Vector2D vector) {
    struct Point milieu;
    milieu.x = (vector.origine.x + vector.destination.x) / 2.0;
    milieu.y = (vector.origine.y + vector.destination.y) / 2.0;
    return milieu;
}

int main() {
    struct Vector2D v;
    struct Point milieu;

    printf("Entrez les coordonnées du point d'origine (x y) : ");
    scanf("%f %f", &v.origine.x, &v.origine.y);

    printf("Entrez les coordonnées du point de destination (x y) : ");
    scanf("%f %f", &v.destination.x, &v.destination.y);

    milieu = get_middle_point(v);

    printf("Le point milieu est : (%.2f, %.2f)\n", milieu.x, milieu.y);

    return 0;
}
