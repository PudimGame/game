#include "menu.h"
#include "stage1.h"
#include "objects.h"
#include "gamefunctions.h"
#include "tilemap.h"
#include "mapa.h"
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define L_JOG 64
#define A_JOG 64
#define GRAV 1
#define MAXG 20
#define SALTO 20
#define NUM_BULLETS 1



ALLEGRO_EVENT mapaev;
void mapa(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int *gameState, bool keys[])
{
    bool pressEnter = false;
    bool drawMap = false;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *pudimbody = NULL;
    ALLEGRO_FONT *font20 = NULL;


    MainHero pudipudao;

        //IMAGENS
    background = al_load_bitmap("./IMGS/MAPA.bmp");

    pudimbody = al_load_bitmap("./IMGS/pudao.png");

    al_init_font_addon();
    al_init_ttf_addon();

    font20 = al_load_font("arial.ttf", 20, 0);
    InitHero(pudipudao, pudimbody, 450, 50);

        //init objects


    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    while(*gameState == MAPA)
    {

        al_wait_for_event(event_queue, &mapaev);
        if(mapaev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *gameState= CLOSE;
        }else if(mapaev.type == ALLEGRO_EVENT_TIMER)
        {
            drawMap = true;
            MoveHero(pudipudao, keys[LEFT], keys[RIGHT]);
            if(keys[UP])
                pudipudao.y -= 4;
            else if (keys[DOWN])
                pudipudao.y += 4;

            if((pudipudao.x > 59 && pudipudao.x < 180)&& (pudipudao.y > 43 && pudipudao.y < 134) )
            {
                pressEnter = true;
                if(keys[ENTER])
                    *gameState = STAGE1;
            }else
                pressEnter = false;


        }else if(mapaev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(mapaev.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = true;
                break;
            }
        }else if(mapaev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(mapaev.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = false;
                break;
            }
        }

        if(drawMap==true && al_event_queue_is_empty(event_queue))
        {
            drawMap = false;
            al_clear_to_color(al_map_rgb(255,0,0));
            al_draw_bitmap(background, 0, 0, 0);
            DrawHero(pudipudao);
            if(pressEnter)
                al_draw_text(font20, al_map_rgb(0,0,0), WIDTH/2, HEIGHT - HEIGHT/6, ALLEGRO_ALIGN_CENTER, "PRESS ENTER!");



            al_flip_display();
        }

    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(pudimbody);

}
