
#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#endif // TILEMAP_H_INCLUDED

#define L_MAPA 20
#define A_MAPA 20
#define TAM_TILE 64

void carregaCenario(char *filename, unsigned char cenario[A_MAPA][L_MAPA]);
//NOVO2909
void desenhaCenario(ALLEGRO_BITMAP *tiles,unsigned char cenario[A_MAPA][L_MAPA], float camera_x, float camera_y);
void drawSpace(ALLEGRO_BITMAP *tiles,unsigned char cenario[A_MAPA][L_MAPA], float camera_x, float camera_y);
bool trataColisao(int largJ, int altJ, float *posX, float *posY, unsigned char cenario[A_MAPA][L_MAPA],boolean up, boolean down, boolean right, boolean left);
