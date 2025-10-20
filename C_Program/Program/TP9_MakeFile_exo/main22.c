#include "library.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void create_line(int size, int red, int green, int blue) {
	for( int i = 0; i < size ; i ++ ) {
		create_square(red, green , blue);
	}
}
void create_empty_line(int size) {
	for( int i = 0; i < size ; i ++ ) {
		create_empty_square();
		}
	}

int main() {
	int size_tree = 1;
    int j = 1;


	printf("Entrez la taille de l'arbre : ");
	scanf("%d", &size_tree);
	
	// Feuillage
    for (int i = 0; i < size_tree; i++) {

        for (int o = 0; o < size_tree - i - 1; o++) {
            create_empty_square();
        }

        // Feuilles qui alterne entre vert et rouge
        for ( j = 0; j < 2 * i + 1; j++) {
            while(j <= 2 * i) {
                create_square(0, 255, 0);
                j++;
                if (j <= 2 * i) {
                    create_square(255, 0, 0);
                    j++;
                    }
                }

             
            
        }

        new_line();
    }

    // Tronc
    int trunk_height = size_tree / 2 + 2;
    int trunk_width = size_tree / 2 + 1;
    int offset = size_tree - trunk_width / 2 - 1;

    for (int t = 0; t < trunk_height; t++) {

        for (int o = 0; o < offset; o++) {
            create_empty_square();
        }

        for (int w = 0; w < trunk_width; w++) {
            create_square(139, 69, 19);
        }

        new_line();
    }
	draw();
    return 0;
}

