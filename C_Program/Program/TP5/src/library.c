#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <time.h>

sfRectangleShape *rectangles[1000];
int current_index = 0;

float base_x = 30;
float base_y = 30;

void add_rectangle(sfRectangleShape* rectangle)
{
	rectangles[current_index] = rectangle;
	current_index++;
}

void display_squares(sfRenderWindow* window)
{
	for(int i = 0 ; i < current_index; i++)
	{
		sfRenderWindow_drawRectangleShape(window, rectangles[i], NULL);
	}
}

void create_square( int red, int green, int blue)
{
	
	sfVector2f position = {base_x, base_y};
	sfVector2f size = {30.0f, 30.0f};
	sfColor color = sfColor_fromRGB(red, green, blue);

	sfRectangleShape *rectangle = sfRectangleShape_create();
    sfRectangleShape_setPosition(rectangle, position);	
    sfRectangleShape_setSize(rectangle, size);
    sfRectangleShape_setFillColor(rectangle, color);

	base_x += 30;

	add_rectangle(rectangle);
}

void new_line()
{
	base_x = 30;
	base_y += 30;
}

void create_empty_square()
{
	base_x += 30;
}

int draw() 
{
    // Create a video mode object
    sfVideoMode mode = {800, 600, 32};

    // Create a window
    sfRenderWindow* window = sfRenderWindow_create(mode, "CSFML Window", sfResize | sfClose, NULL);

    if (!window) return 1;


    // Main loop to keep the window open
    while (sfRenderWindow_isOpen(window)) 
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) 
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // Clear the window with black color
        sfRenderWindow_clear(window, sfBlack);

		display_squares(window);
		

        // Display the window
        sfRenderWindow_display(window);
    }

    // Destroy the window after use
    sfRenderWindow_destroy(window);
    return 0;
}
