#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <math.h>

struct Point {
    float x;
    float y;
};

struct Vector2D {
    struct Point origine;
    struct Point destination;
};

// Fonction qui retourne le point milieu d’un vecteur
float get_vector_distance(struct Vector2D vector) {
    float distance;
    distance = sqrt(pow((vector.destination.x - vector.origine.x), 2) + pow((vector.destination.y - vector.origine.y), 2));
    return distance;
}

int main() {
    struct Vector2D v;
    float distance;

    printf("Entrez les coordonnées du point d'origine (x y) : ");
    scanf("%f %f", &v.origine.x, &v.origine.y);

    printf("Entrez les coordonnées du point de destination (x y) : ");
    scanf("%f %f", &v.destination.x, &v.destination.y);

    distance = get_vector_distance(v);

    printf("La distance du vecteur est : (%.2f)\n", distance);

    return 0;
}
