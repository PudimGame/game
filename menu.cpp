#include "menu.h"

ALLEGRO_EVENT menuev;
void mainMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int *gameState, bool keys[])
{
    ALLEGRO_BITMAP *menu;

    //Carrega imagens utilizadas no menu
    menu = al_load_bitmap("menu.png");
    if(!menu)
    {
        al_show_native_message_box(display, "Erro", "Erro", "Falha no carregamento de menu.png",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(9);
    }

    //quadros do jogo
    int but1frame=0;
    int but2frame=2;
    bool drawMenu=true;

    //evento
    while(*gameState==MENU)
    {
        al_wait_for_event(event_queue, &menuev);
        if(menuev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)   //Se recebeu um evento do tipo definido (clicar no x pra fechar a janela), faça:
        {
            *gameState= CLOSE;
        }
        //TRATA EVENTOS MOUSE
        else if(menuev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            but1frame=0;
            but2frame=2;

            //ev.mouse.x e ev.mouse.y são as coordenadas do mouse na tela
            if(menuev.mouse.x>WIDTH/2.0-128 && menuev.mouse.x<WIDTH/2.0+128 && menuev.mouse.y>HEIGHT/2-100 && menuev.mouse.y<HEIGHT/2-36)
            {
                //*gameState=ANIM1;
                *gameState=ANIM1;
            }
            else if (menuev.mouse.x>WIDTH/2.0-128 && menuev.mouse.x<WIDTH/2.0+128 && menuev.mouse.y>HEIGHT/2-32 && menuev.mouse.y<HEIGHT/2+32)
            {
                //Sai do jogo garantindo que toda a memória será liberada
                menuev.type=ALLEGRO_EVENT_DISPLAY_CLOSE;
                *gameState=CLOSE;
            }

        }
        else if(menuev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            //verifica se está sendo clicado dentro da opção 1
            if(menuev.mouse.x>WIDTH/2.0-128 && menuev.mouse.x<WIDTH/2.0+128 && menuev.mouse.y>HEIGHT/2 -100 && menuev.mouse.y<HEIGHT/2-36)
            {
                but1frame=1;
            }
            else if(menuev.mouse.x>WIDTH/2.0-128 && menuev.mouse.x<WIDTH/2.0+128 && menuev.mouse.y>HEIGHT/2-32 && menuev.mouse.y<HEIGHT/2+32)
            {
                but2frame=3;
            }

        }
       else if(menuev.type == ALLEGRO_EVENT_TIMER)
       {
           drawMenu=true;
       }
       if(drawMenu==true && al_event_queue_is_empty(event_queue))
       {
        al_clear_to_color(al_map_rgb(100,100,255));
        al_draw_bitmap_region(menu,0,but1frame*64,256,64, WIDTH/2.0-128,HEIGHT/2-100, 0);
        al_draw_bitmap_region(menu,0,but2frame*64,256,64, WIDTH/2.0-128,HEIGHT/2-32, 0);

        al_flip_display();
       }
    }

    //NOVO7: Liberar memória utilizada no jogo
    al_destroy_bitmap(menu);
}
