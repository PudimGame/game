#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 60
#define MARGEM 100

enum GAMESTATES{MENU, MAPA, ANIM1, STAGE1, STAGE2, STAGE3, CLOSE};

void mainMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int *gameState, bool keys[]);

enum KEYS{LEFT, RIGHT, UP, DOWN, ENTER};



#endif // MENU_H_INCLUDED
