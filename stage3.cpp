#include "menu.h"
#include "stage3.h"
#include "objects.h"
#include "gamefunctions.h"
#include "tilemap.h"


ALLEGRO_EVENT stagethreeev;
void stageThree(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue,int *gameState, bool keys)
{
    ALLEGRO_BITMAP *stage3 = NULL;
    ALLEGRO_BITMAP *kombi = NULL;

    stage3 = al_load_bitmap("./mapas/space.png");
    //kombi = al_load_bitmap("kombi128x64.png");

    int counter = 0;
    unsigned char camadaFundo[A_MAPA][L_MAPA];

    carregaCenario("./mapas/space",camadaFundo);
    al_register_event_source(event_queue, al_get_display_event_source(display));

    BG bg;

    bg.x = 0;
    bg.y = 0;
    bg.speed = 2;
        while(*gameState == STAGE3)
    {

        al_wait_for_event(event_queue, &stagethreeev);

         if(stagethreeev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *gameState= CLOSE;
        }if(stagethreeev.type == ALLEGRO_EVENT_TIMER)
        {
         bg.x--;
         if (bg.x + 832 <= 0)
            bg.x = 0;

        }


        drawSpace(stage3,camadaFundo, bg.x, bg.y);
        if(bg.x + 832 < 800)
            drawSpace(stage3,camadaFundo, bg.x+832, bg.y);
        al_flip_display();


    }
}
