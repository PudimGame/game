#include "menu.h"
#include "stage1.h"
#include "objects.h"
#include "gamefunctions.h"
#include "tilemap.h"
#include <stdio.h>
#define L_JOG 64
#define A_JOG 64
#define GRAV 1
#define MAXG 20
#define SALTO 20
#define NUM_BULLETS 1
void InitBullet(Bullet bullet[], int size, MainHero &pudim);
void DrawBullet(Bullet bullet[], int size, float camera_x, float camera_y);
void UpdateBullet(Bullet bullet[], int size, bool fireLeft, float camera_x);
void FireBullet(Bullet bullet[], int size, MainHero &pudim,float camera_x, float camera_y);

ALLEGRO_EVENT stageoneev;

void animOne(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int *gameState, bool keys[])
{
    bool drawAnim1 = false;

    int animCounter = 0;
    int fala;
    enum FALAS{NOFALA, FALA1, FALA2, FALA3, FALA4, FALAFINISH};
    bool blackbox = false;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *padeiroface = NULL;
    ALLEGRO_BITMAP *pudimface = NULL;

    ALLEGRO_BITMAP *pudimbody = NULL;
    ALLEGRO_BITMAP *bandidoface= NULL;

    MainHero pudipudao;
    AnimImagem cmesa;
    AnimImagem cpadeiro;
    AnimImagem cbandidoface;
    AnimImagem cpudimface;
        //IMAGENS
    background = al_load_bitmap("./IMGS/an.jpg");
    padeiroface = al_load_bitmap("./IMGS/marcio.png");
    pudimbody = al_load_bitmap("./IMGS/pudao.png");
    bandidoface = al_load_bitmap("./IMGS/bandidoface.png");
    pudimface = al_load_bitmap("./IMGS/pudimface.png");

    InitHero(pudipudao, pudimbody, 20, 200);

        //init objects
    InitImage(cbandidoface, bandidoface, 0 - al_get_bitmap_width(bandidoface), 350);
    InitImage( cpadeiro, padeiroface, 0 - al_get_bitmap_width(padeiroface), 350);
    InitImage( cpudimface, pudimface, 0 - al_get_bitmap_width(pudimface), 350);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    while(*gameState == ANIM1)
    {

        al_wait_for_event(event_queue, &stageoneev);
        if(stageoneev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *gameState= CLOSE;
        }else if(stageoneev.type == ALLEGRO_EVENT_TIMER)
        {
            drawAnim1 = true;
            animCounter++;
                if(animCounter > 10 && animCounter < 250)
                {
                    blackbox = true;
                    //anim = ANIM1;
                    fala = FALA1;
                    MoveImage(cpadeiro, 0, 300);
                    if(animCounter == 249 && !keys[ENTER])
                        animCounter = 248;


                }
                if ( (animCounter >= 250 && animCounter < 500) ||
                     (animCounter >= 700 && animCounter < 800) ||
                     (animCounter >= 1000 && animCounter < 1500))
                {
                    blackbox = false;
                    //anim = NOANIM;
                    fala = NOFALA;
                    cpadeiro.x = 0 - al_get_bitmap_width(padeiroface);
                    cbandidoface.x = 0 - al_get_bitmap_width(bandidoface);
                    cpudimface.x = 0 - al_get_bitmap_width(pudimface);
                    if(animCounter >= 900)
                        *gameState = STAGE1;
                        //anim = ANIMFINISH;
                }
                if (animCounter >= 500 && animCounter < 700)
                {
                    blackbox = true;
                    //anim = ANIM2;
                    fala = FALA2;
                    MoveImage(cbandidoface, 0, 300);
                    if(animCounter == 699 && !keys[ENTER])
                        animCounter = 698;
                }

                if (animCounter >= 800 && animCounter < 1000)
                {
                    blackbox = true;
                    //anim = ANIM2;
                    fala = FALA3;
                    MoveImage(cpudimface, 0, 300);
                    if(animCounter == 999 && !keys[ENTER])
                        animCounter = 998;
                }

        }else if(stageoneev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(stageoneev.keyboard.keycode)
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
        }else if(stageoneev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(stageoneev.keyboard.keycode)
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

        if(drawAnim1==true && al_event_queue_is_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(255,0,0));
            al_draw_bitmap(background, 0, 0, 0);
            //DrawHero(pudipudao);
            al_draw_filled_rectangle(0, 317, WIDTH, HEIGHT, al_map_rgba(0,0,0,200));
            if(blackbox && fala != NOFALA)
            {

                if(fala == FALA1)
                    DrawRegionImage(cpadeiro, 2, 148, 191);
                else if (fala == FALA2)
                    DrawRegionImage(cbandidoface, 0, 148, 191);
                else if (fala == FALA3)
                    DrawRegionImage(cpudimface, 0, 65, 48);

            }

            al_flip_display();
        }

    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(pudimbody);
    al_destroy_bitmap(pudimface);
    al_destroy_bitmap(bandidoface);
    al_destroy_bitmap(padeiroface);

}
void stageOne(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int *gameState, bool keys[])
{
    enum BOSS{STAY, DASHRIGHT, DASHLEFT, ATTACK, JUMP};
    int bossAction = STAY;
    float bulletDistance;
    bool drawStage1 = false;
    bool cima = false;
    bool baixo = false;
    bool direita = false;
    bool esquerda = false;
    bool bossesquerda = false;
    bool bossdireita = false;
    bool bosscima = false;
    bool bossbaixo = false;
    bool saltando = false;
    bool justDashed = true;
    bool justJumped = false;
    int dashCoolDown = 30; // 5 segundos
    int jumpCoolDown = 120;
    float jog_dy=0;
    float boss_dy =0;
    bool fireLeft = false;
    float camera_x = 0;
    float camera_y = 0;

    Bullet bullets[NUM_BULLETS];

    ALLEGRO_BITMAP *background = NULL;
    //ALLEGRO_BITMAP *padeiroface = NULL;
    //ALLEGRO_BITMAP *pudimface = NULL;

    ALLEGRO_BITMAP *pudimbody = NULL;
    ALLEGRO_BITMAP *bossbody = NULL;
    //ALLEGRO_BITMAP *padeirobody= NULL;

    MainHero pudipudao;

    FirstBoss firstBoss;
    //AnimImagem cmesa;
    //AnimImagem cpadeiro;
    //AnimImagem cpadeirobody;

        //IMAGENS
    background = al_load_bitmap("./pm/lul.png");
    //padeiroface = al_load_bitmap("./IMGS/marcio.png");
    pudimbody = al_load_bitmap("./IMGS/pudao.png");
    bossbody = al_load_bitmap("boss.png");
    //padeirobody = al_load_bitmap("./IMGS/padeiro.png");

    //unsigned char camadaFundo[A_MAPA][L_MAPA];
    unsigned char camadaColisao[A_MAPA][L_MAPA];
    unsigned char camadaFundo[A_MAPA][L_MAPA];
    InitHero(pudipudao, pudimbody, 150, 1151);
    InitBoss(firstBoss, bossbody, 300, 1087);
    InitBullet(bullets, NUM_BULLETS,pudipudao);

    al_install_mouse();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    //carregaCenario("./mapas/bg",camadaFundo);
    carregaCenario("./mapas/bgac",camadaColisao);
    carregaCenario("./mapas/bg",camadaFundo);
    while(*gameState == STAGE1)
    {

        al_wait_for_event(event_queue, &stageoneev);
        if(stageoneev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *gameState= CLOSE;
        }else if(stageoneev.type == ALLEGRO_EVENT_TIMER)
        {
            /*if(pudipudao.x > 800)
                *gameState = STAGE3;*/
            drawStage1 = true;
            if(!bullets[0].live)
                fireLeft = pudipudao.x > firstBoss.x;

            UpdateBullet(bullets, NUM_BULLETS, fireLeft, camera_x);
            MoveHero(pudipudao, keys[LEFT],keys[RIGHT]);

            if(direita)
            {
                pudipudao.x+=4;
                /*firstBoss.x += 4;
                bossdireita = true;
                bossesquerda = false;*/

            }
            else if(esquerda)
            {
                pudipudao.x-=4;
                /*firstBoss.x -= 25;
                bossesquerda = true;
                bossdireita = false;*/
            }
          //NOVO2509
          //Após mover em x, trata colisão em x
          pudipudao.x+=3;
          pudipudao.y+=3;
          trataColisao(L_JOG-7.5,A_JOG-24,&pudipudao.x,&pudipudao.y,camadaColisao,false,false,direita,esquerda);
          pudipudao.x-=3;
          pudipudao.y-=3;

          //NOVO0210
          pudipudao.y+=jog_dy;
          jog_dy+=GRAV;
          if(jog_dy>MAXG) jog_dy=MAXG;
          if(jog_dy<0)
          {
              cima=true;
              baixo=false;
          }
          else
          {
              cima=false;
              baixo=true;
          }

          //NOVO2509
          //Após mover em y, trata colisão em y
          pudipudao.x+=3;
          pudipudao.y+=3;
          bool colidiuY = trataColisao(L_JOG-7.5,A_JOG-24,&pudipudao.x,&pudipudao.y,camadaColisao,cima,baixo,false,false);
          pudipudao.x-=3;
          pudipudao.y-=3;

          if(colidiuY)
          {
              if(baixo)
                saltando = false;
              jog_dy=0;
          }





          firstBoss.x+=5;
          firstBoss.y+=5;
          bool bossColidiuX = trataColisao(63,124,&firstBoss.x,&firstBoss.y,camadaColisao,false,false,bossdireita,bossesquerda);
          firstBoss.x-=5;
          firstBoss.y-=5;
          if(bossColidiuX)
            firstBoss.speed = 0;
          else
            firstBoss.speed = 50;

          //printf("colidiu %d\n", bossColidiuX);

          //NOVO0210
          firstBoss.y+=boss_dy;
          boss_dy+=GRAV;
          if(boss_dy>MAXG)
            boss_dy=MAXG;
          if(boss_dy<0)
          {
              bosscima=true;
              bossbaixo=false;
          }
          else
          {
              bosscima=false;
              bossbaixo=true;
          }

          //NOVO2509
          //Após mover em y, trata colisão em y
          firstBoss.x+=5;
          firstBoss.y+=5;
          bool bossColidiuY = trataColisao(60,128,&firstBoss.x,&firstBoss.y,camadaColisao,bosscima,bossbaixo,false,false);
          firstBoss.x-=5;
          firstBoss.y-=5;
          //printf("Y %f\n", firstBoss.y);

            //printf("%d %d %d %d \n", bosscima, bossbaixo, bossesquerda, bossdireita);
          if(bossColidiuY)
          {
              boss_dy=0;
          }











          switch(bossAction)
          {
          case STAY:

              if((pudipudao.x-firstBoss.x < -50) && !justDashed )
                {
                    bossAction = DASHLEFT;
                    /*bossdireita = false;
                    bossesquerda = true;*/
                }
              else if ((pudipudao.x-firstBoss.x > 50) && !justDashed)
                {
                    bossAction = DASHRIGHT;

                    /*bossdireita = true;
                    bossesquerda = false;*/
                }
              if(dashCoolDown > 0 && justDashed)
              {
                dashCoolDown--;
              }else
              {
                dashCoolDown = 60;
                justDashed = false;
              }
              printf("a %f b %f\n", bullets[0].y , firstBoss.y );
              bulletDistance = firstBoss.x - bullets[0].x;
              if(bulletDistance < 0)
                bulletDistance = -(bulletDistance);
              if(bullets[0].live && bulletDistance < 150 && bullets[0].y > firstBoss.y  && !justJumped)
                {
                    printf("a %f b %f\n", bullets[0].y , firstBoss.y );
                    bossAction = JUMP;
                    justJumped = true;
                }
            if(justJumped && jumpCoolDown > 0)
                jumpCoolDown--;
            else
            {
                justJumped = false;
                jumpCoolDown = 120;
            }


            break;
          case ATTACK:
            break;
          case DASHRIGHT:
            bossdireita = true;
            firstBoss.x += firstBoss.speed;
            if(bossColidiuX)
            {
                bossAction = STAY;
                justDashed = true;
                bossdireita = false;
            }


            break;
          case DASHLEFT:
              bossesquerda = true;
            firstBoss.x -= firstBoss.speed;
            if(bossColidiuX)
            {
                bossAction = STAY;
                justDashed = true;
                bossesquerda = false;
            }


            break;
          case JUMP:

              boss_dy -= SALTO;
              bossAction = STAY;
            break;
          }
          //printf("%d\n", dashCoolDown);
          if(pudipudao.x-camera_x<MARGEM) camera_x=pudipudao.x-MARGEM;
          if(pudipudao.x-camera_x>WIDTH-MARGEM-L_JOG) camera_x=pudipudao.x-(WIDTH-MARGEM-L_JOG);

          if(pudipudao.y-camera_y<45) camera_y=pudipudao.y-45;
          if(pudipudao.y-camera_y>HEIGHT-45-A_JOG) camera_y=pudipudao.y-(HEIGHT-45-A_JOG);





        }else if(stageoneev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(stageoneev.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_W:
                if(saltando==false)
                {
                    saltando=true;
                    jog_dy-=SALTO;

                }
                break;
            case ALLEGRO_KEY_A:
                esquerda=true;
                break;
            case ALLEGRO_KEY_D:
                direita=true;
                break;
            case ALLEGRO_KEY_SPACE:
                FireBullet(bullets, NUM_BULLETS, pudipudao,camera_x,camera_y);
                break;
            }
        }else if(stageoneev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(stageoneev.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_UP:
                break;
            case ALLEGRO_KEY_A:
                esquerda=false;
                break;
            case ALLEGRO_KEY_D:
                direita=false;
                break;
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = false;
                break;
            }
        }else if(stageoneev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            /*if(stageoneev.mouse.x < pudipudao.x)
                fireLeft = true;
            else
                fireLeft = false;*/
        }

        if(drawStage1==true && al_event_queue_is_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(255,0,0));
            //al_draw_bitmap(background, 0, 0, 0);
            //desenhaCenario(background,camadaFundo, 0, 0);
            desenhaCenario(background,camadaColisao, camera_x, camera_y);
            desenhaCenario(background,camadaFundo, camera_x, camera_y);
            //DrawHero(pudipudao);
            al_draw_bitmap(pudipudao.image, pudipudao.x-camera_x, pudipudao.y-camera_y, 0);
            al_draw_bitmap(firstBoss.image, firstBoss.x-camera_x+5, firstBoss.y+5-camera_y, 0);
            DrawBullet(bullets, NUM_BULLETS, camera_x,camera_y);
            al_flip_display();
        }

    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(pudimbody);
    //al_destroy_bitmap(pudimface);
    //al_destroy_bitmap(padeirobody);
    //al_destroy_bitmap(padeiroface);

}

void InitBullet(Bullet bullet[], int size, MainHero &pudim)
{
    for(int i = 0; i < size; i++)
    {
        bullet[i].id = BULLET;
        bullet[i].x = pudim.x-32;
        bullet[i].y =  pudim.y - 32;
        bullet[i].live = false;
        bullet[i].speed = 15;
    }

}
void DrawBullet(Bullet bullet[], int size, float camera_x, float camera_y)
{

    for(int i = 0; i < size; i++)
    {
        if(bullet[i].live)
        {
            al_draw_filled_circle(bullet[i].x-camera_x, bullet[i].y-camera_y, 3, al_map_rgb(0,0,0));
        }
    }

}
void FireBullet(Bullet bullet[], int size, MainHero &pudim,float camera_x, float camera_y)
{
    for( int i = 0; i < size; i++ )
    {
        if(!bullet[i].live)
        {
            bullet[i].x = pudim.x + 20;
            bullet[i].y = pudim.y + 25;
            bullet[i].live = true;
            break;
        }
    }
}
void UpdateBullet(Bullet bullet[], int size, bool fireLeft, float camera_x)
{
        for(int i = 0;i < size; i++)
        {
        if(bullet[i].live)
        {
            if(fireLeft)
                bullet[i].x -= bullet[i].speed;
            else
                bullet[i].x += bullet[i].speed;




                if(bullet[i].x < camera_x || bullet[i].x > camera_x + WIDTH)
                    bullet[i].live = false;
        }
    }
}
