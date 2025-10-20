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
	for (int i = 0; i < 10;i++){
        for (int j = 0; j < 10;j++){
            if (i==j)
            create_square(255, 0 , 0);
            else 
            create_square(0,255,0);
        }
        new_line();
    }
	draw();
    return 0;
}

