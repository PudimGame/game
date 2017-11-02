#ifndef GAMEFUNCTIONS_H_INCLUDED
#define GAMEFUNCTIONS_H_INCLUDED
//FUNCOES
void InitImage(AnimImagem &imagem, ALLEGRO_BITMAP *image, int x, int y);
void DrawImage(AnimImagem &imagem);
void MoveImage(AnimImagem &image, int finalX, int finalY);
void DrawRegionImage(AnimImagem &imagem, int curFrame, int width, int height);

//PLAYER
void InitHero(MainHero &player, ALLEGRO_BITMAP *image, int x, int y);
void DrawHero(MainHero &player);
void MoveHero(MainHero &player, bool LEFT, bool RIGHT);
//boss
void InitBoss(FirstBoss &boss, ALLEGRO_BITMAP *image, int x, int y);

#endif // GAMEFUNCTIONS_H_INCLUDED
