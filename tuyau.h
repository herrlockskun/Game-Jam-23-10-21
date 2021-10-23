#ifndef TUYAU_H
#define TUYAU_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define TAILLE_MAP 5

typedef struct tuyau
{

}tuyau_t;


enum CaseMap
{
    sol,
    montagne,
    tuyau
};


enum 

void print_map_console(enum CaseMap map[TAILLE_MAP][TAILLE_MAP]);
void print_case_console(enum CaseMap caseMap);




#endif
