#ifndef menu_gard
#define menu_gard


// #dsefine OFFSETX 900
// #define OFFSETY 300

#include "background.h"
#include "const.h"

void dessinfond(SDL_Renderer *renderer, SDL_Texture *bg[2], int centre);

void dessinargent(SDL_Renderer *renderer, TTF_Font* font1, int money, SDL_Texture *bg[2]);

void constructbat(SDL_Renderer *renderer, TTF_Font *font1,int type);

void editiontuyaux(SDL_Renderer *renderer, TTF_Font *font1);

void affichemenu(SDL_Renderer *renderer,int money, TTF_Font* font1, int status);

void eventmenu(int posx, int posy, int* status);

#endif