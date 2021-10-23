#include "menu.h"
//gcc  menu.c -o prog -lSDL2 -lSDL2_image -lSDL2_ttf

void dessinfond(SDL_Renderer *renderer, SDL_Texture *bg[2], int centre)
{
    SDL_Rect destination;
    destination.x = OFFSETX;
    destination.w = 300;
    if (centre)
    {
        destination.y=240;
        destination.h=500;
        SDL_RenderCopy(renderer, bg[0], NULL, &destination);
    }
    else
    {
        destination.h=240;
        destination.y=0;
        SDL_RenderCopy(renderer, bg[0], NULL, &destination);
        destination.y=750;
        destination.h=150;
        SDL_RenderCopy(renderer, bg[0], NULL, &destination);
    }
}


void dessinmenu(SDL_Renderer *renderer, TTF_Font *font1, int money, SDL_Texture *bg[2])
{
    //mise en place du fond de la partie menu

    SDL_Rect destination,source;
    dessinfond(renderer,bg,0);

    //écriture du mot "argent :"
    char *argent = "Argent :";
    SDL_Texture *text;
    SDL_Color couleur = {9, 106, 9, 255};
    SDL_Surface *surf = TTF_RenderText_Blended(font1, argent, couleur);
    text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    destination.x = OFFSETX + 20;
    destination.y = 25;
    destination.w = 260;
    destination.h = 100;
    SDL_RenderCopy(renderer, text, NULL, &destination);

    //écriture de la somme d'argent possédé
    char sous[10];
    sprintf(sous, "%d", money);
    strcat(sous, "$");
    SDL_Color couleur2 = {255, 140, 0, 255};
    surf = TTF_RenderText_Blended(font1, sous, couleur2);
    text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    destination.y = 130;
    destination.w = (int)260.0 * ((float)strlen(sous) / 10);
    SDL_RenderCopy(renderer, text, NULL, &destination);
    
    //placement des boutons
    source.x = 240;
    source.y = 60;
    source.h = 420;
    source.w = 420;
    destination.h = 80;
    destination.w = 80;
    destination.y = OFFSETY + 450;
    for (int k = 0; k < 3; k++)
    {
        destination.x = OFFSETX+10 + 100 * k;
        SDL_RenderCopy(renderer, bg[1], &source, &destination);
    }
}

void affichemenu(SDL_Renderer *renderer,int money, TTF_Font* font1)
{
    SDL_Texture *bg[2];
    bg[0]=load_texture_from_image("cosmos.jpeg", renderer);
    bg[1]=load_texture_from_image("bouton.png", renderer);
    dessinmenu(renderer, font1,money, bg);
}

void eventmenu(int posx, int posy)
{
    if (posy>750 && posy<830)
    {
        if (posx>910 && posx<990)
        {
            //lancer l'édition des tuyaux
        }
        if (posx>1010 && posx<1090)
        {
            //lancer sous menu des extracteurs
        }
        if (posx>1110 && posx<1190)
        {
            //lancer sous menu des usines
        }
    }
}