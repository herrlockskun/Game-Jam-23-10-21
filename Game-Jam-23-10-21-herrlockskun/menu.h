#ifndef menu_gard
#define menu_gard

#define OFFSETX 900
#define OFFSETY 300

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "background.h"

void dessinmenu(SDL_Renderer *renderer, TTF_Font* font1, int money, SDL_Texture *bg[2]);

void mainmenu(SDL_Renderer *renderer,int money, TTF_Font* font1);


#endif