#include "menu.h"
//gcc  menu.c -o prog -lSDL2 -lSDL2_image -lSDL2_ttf

void dessinmenu(SDL_Renderer *renderer, TTF_Font *font1, int money, SDL_Texture *bg[2])
{

    char *argent = "Argent :";
    SDL_Texture *text;
    SDL_Rect destination, source;
    destination.x = OFFSETX;
    destination.y = 0;
    destination.w = 300;
    destination.h = 600; //PENSER A CHANGER !!!!!!!!!!!
    SDL_RenderCopy(renderer, bg[0], NULL, &destination);

    SDL_Color couleur = {9, 106, 9, 255};
    SDL_Surface *surf = TTF_RenderText_Blended(font1, argent, couleur);
    text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    destination.x = OFFSETX + 20;
    destination.y = 25;
    destination.w = 260;
    destination.h = 100;
    SDL_RenderCopy(renderer, text, NULL, &destination);

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

    source.x = 240;
    source.y = 60;
    source.h = 420;
    source.w = 420;
    destination.h = 80;
    destination.w = 80;
    destination.y = OFFSETY + 450;
    for (int k = 0; k < 3; k++)
    {
        destination.x = 10 + 100 * k;
        SDL_RenderCopy(renderer, bg[1], &source, &destination);
    }
}

void mainmenu(SDL_Renderer *renderer,int money)
{
    TTF_Font *font1;

    font1 = TTF_OpenFont("arial.ttf", 60);
    SDL_Texture *bg[2];
    bg[0]=load_texture_from_image("cosmos.jpeg", renderer);
    bg[1]=load_texture_from_image("bouton.png", renderer);
    dessinmenu(renderer, font1,money, bg);
    TTF_CloseFont(font1);
    TTF_Quit();

}