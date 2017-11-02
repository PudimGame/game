
#include <stdio.h>
#include "tilemap.h"

void carregaCenario(char *filename, unsigned char cenario[A_MAPA][L_MAPA])
{

    char value;
    int c=0;
    int i=0, j=0;
    FILE *input;
    input = fopen(filename,"r");
    if(input==NULL)
    {
        printf("Nao foi possivel abrir arquivo com mapa %s",filename);
        return;
    }
    fscanf(input,"%c",&value);
    while(!feof(input))
    {
        cenario[j][i]=value;
        fscanf(input,"%c",&value);
        i++;
        if(i%L_MAPA==0) { j++; i=0;}

    }
    fclose (input);
}

//NOVO2909: alteracao para desenhar com a câmera
void desenhaCenario(ALLEGRO_BITMAP *tiles,unsigned char cenario[A_MAPA][L_MAPA], float camera_x, float camera_y)
{
    int i, j;
    for(i=0;i<L_MAPA;i++)
    {
        for(j=0;j<A_MAPA;j++)
        {
            if(cenario[j][i]!=255)
                al_draw_bitmap_region(tiles,cenario[j][i]*TAM_TILE,0,TAM_TILE,TAM_TILE,
                                      i*TAM_TILE-camera_x,j*TAM_TILE-camera_y,0);
        }
    }
}
void drawSpace(ALLEGRO_BITMAP *tiles,unsigned char cenario[A_MAPA][L_MAPA], float x, float y)
{
    int i, j;
    for(i=0;i<L_MAPA;i++)
    {
        for(j=0;j<A_MAPA;j++)
        {
            if(cenario[j][i]!= 13)
            {

                al_draw_bitmap_region(tiles,cenario[j][i]*TAM_TILE,0,TAM_TILE,TAM_TILE,
                                      i*TAM_TILE+x,j*TAM_TILE+y,0);

            }

        }
    }
}

bool trataColisao(int largJ, int altJ, float *posX, float *posY, unsigned char cenario[A_MAPA][L_MAPA],boolean cima, boolean baixo, boolean direita, boolean esquerda)
{
    int ix_1 = (*posX)/TAM_TILE;
    int iy_1 = (*posY)/TAM_TILE;
    int ix_2 = ((*posX)+largJ)/TAM_TILE;
    int iy_2 = ((*posY)+altJ)/TAM_TILE;
    int i,j;



    for(i = ix_1;i >= 0 && i < L_MAPA && i <= ix_2;i++)
    {
        for(j = iy_1;j >= 0 && j < A_MAPA && j <= iy_2;j++)
        {
            if(cenario[j][i] != 255) //Colisão
            {
                //printf("%d %d\n", cima,baixo);


                if (baixo && (j*TAM_TILE > *posY))
                    *posY=j*TAM_TILE-altJ-1;
                else if(cima&&(j*TAM_TILE<*posY))
                    *posY=(j+1)*TAM_TILE+1;
                if (direita&&(i*TAM_TILE>*posX))
                    *posX=(i*TAM_TILE)-largJ-1;
                else if(esquerda&&(i*TAM_TILE<*posX))
                    *posX=(i+1)*TAM_TILE+1;
                return true;

            }
        }
    }
    return false;
}
