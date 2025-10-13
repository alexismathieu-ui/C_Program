#include "library.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void create_line(int size, int red, int green, int blue) {
	for( int i = 0; i < size ; i ++ ) {
		create_square(red, green , blue);
	}
}

int main() {
    int size = 1;
    int i = 1;
    printf("Entrez la taille de la ligne de carrés : ");
    scanf("%d", &size);
    for( i = 0; i < size ; i ++ ) {
	    create_square(0, 0, 255);
	    draw();
    }
    return 0;
}
