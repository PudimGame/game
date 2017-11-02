#include "menu.h"
#include "stage1.h"
#include "objects.h"



void InitImage(AnimImagem &imagem, ALLEGRO_BITMAP *image, int x, int y)
{
    imagem.x = x;
    imagem.y = y;
    imagem.image = image;
}
void DrawImage(AnimImagem &imagem)
{
    al_draw_bitmap(imagem.image, imagem.x, imagem.y, 0);
}

void DrawRegionImage(AnimImagem &imagem, int curFrame, int width, int height)
{
    al_draw_bitmap_region(imagem.image, curFrame * width, 0, width, height, imagem.x, imagem.y, 0 );
}
void MoveImage(AnimImagem &image, int finalX, int finalY)
{
    if(image.x < finalX)
        image.x += 10;
}
//PLAYER
void InitHero(MainHero &player, ALLEGRO_BITMAP *image, int x, int y)
{
    player.x = x;
    player.y = y;
    player.image = image;
    player.lives = 50;
    player.boundx = 25;
    player.boundy = 25;
    player.speed = 4;
    player.id = PLAYER;

}
void DrawHero(MainHero &player)
{
    al_draw_bitmap(player.image, player.x, player.y, 0);
}
void MoveHero(MainHero &player, bool LEFT, bool RIGHT)
{
    if(LEFT)
    {
        player.x -= player.speed;
    }
    if(RIGHT)
    {
        player.x += player.speed;
    }
}

void InitBoss(FirstBoss &boss, ALLEGRO_BITMAP *image, int x, int y)
{
    boss.x = x;
    boss.y = y;
    boss.image = image;
    boss.life = 50;
    boss.speed = 4;
    boss.id = ENEMY;

}
