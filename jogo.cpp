/*#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>*/
#include "menu.h"
#include "stage1.h"
#include "stage3.h"
#include "mapa.h"
int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    int gameState = MENU;
    ALLEGRO_EVENT ev;



    bool keys[] = {false, false, false, false, false};



    if(!al_init())
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na inicialização",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    display = al_create_display(WIDTH,HEIGHT);
    if(!display)
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na inicialização do display",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 2;
    } else al_set_window_position(display,100,100);

    //NOVO1:
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na inicialização da fila de eventos",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 3;
    }
    //NOVO2:
    timer = al_create_timer(1.0/FPS);
    if(!timer)
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na inicialização do timer",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 4;
    }

    //NOVO3:
    if(!al_init_image_addon())
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na inicializacao de image addon",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 5;
    }

        //NOVO4:
    if(!al_install_keyboard())
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha na instalacao do teclado",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 8;
    }

    //NOVO8: Instala mouse
    if(!al_install_mouse()) {
      al_show_native_message_box(display, "Erro", "Erro", "Falha ao iniciar o mouse.",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 10;
   }
    al_init_primitives_addon();


    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_mouse_event_source());


    while(1)
    {
        //al_wait_for_event(event_queue, &ev);

        switch(gameState)
        {
        case MAPA:
            mapa(display,event_queue,&gameState, keys);
            break;
        case MENU:
            mainMenu(display,event_queue,&gameState, keys);
            break;
        case ANIM1:
            animOne(display,event_queue,&gameState,keys);
            break;
        case STAGE1:
            stageOne(display,event_queue,&gameState, keys);
            break;
        case STAGE3:
            stageThree(display,event_queue,&gameState, keys);
            break;
        case CLOSE:
            return -20;
            break;

        }
    }

    return 0;
}
