#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

enum IDS{PLAYER, ENEMY, BULLET};

struct AnimImagem
{
    int x;
    int y;

    ALLEGRO_BITMAP *image;
};

struct MainHero
{
    int id;
    float x;
    float y;
    float speed;
    int lives;
    int boundx;
    int boundy;

    ALLEGRO_BITMAP *image;

};

struct FirstBoss
{
    int id;
    float x;
    float y;
    float speed;
    int life;

    ALLEGRO_BITMAP *image;

};

struct BG
{
    float x;
    float y;
    int speed;

};

struct Bullet
{
    int id;
    float x;
    float y;
    bool live;
    float speed;
};


#endif
