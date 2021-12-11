#include "menu.h"
//gcc  menu.c -o prog -lSDL2 -lSDL2_image -lSDL2_ttf

/*void dessinfond(SDL_Renderer *renderer, SDL_Texture *bg[2], int centre)
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
}*/

void dessinargent(SDL_Renderer *renderer, TTF_Font *font1, int money, SDL_Texture *bg[2])
{
    SDL_Rect destination, source;
    char *argent = "Argent :";
    SDL_Texture *text;

    //mise en place du fond de la partie menu
    destination.x = OFFSETX;
    destination.w = LARGEUR_MENU;
    destination.h = HAUTEUR_FENETRE;
    destination.y = 0;
    SDL_RenderCopy(renderer, bg[0], NULL, &destination);

    //écriture du mot "argent :"

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
        destination.x = OFFSETX + 10 + 100 * k;
        SDL_RenderCopy(renderer, bg[1], &source, &destination);
    }
}

void editiontuyaux(SDL_Renderer *renderer, TTF_Font *font1)
{
    SDL_Texture *ttuto1, *ttuto2, *ttuto3, *tannulation, *tannul;
    char *tuto1 = "Cliquez sur le batiment de depart";
    char *tuto2 = "puis sur tout le trajet";
    char *tuto3 = "puis sur le batiment d'arrive";
    char *annulation = "Annuler le dernier place";
    char *annul = "Annuler la construction";
    SDL_Rect destination;
    SDL_Surface *surf;

    SDL_Color couleur = {100, 100, 100, 255};
    surf = TTF_RenderText_Blended(font1, tuto1, couleur);
    ttuto1 = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Blended(font1, tuto2, couleur);
    ttuto2 = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Blended(font1, tuto3, couleur);
    ttuto3 = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    destination.x = OFFSETX + 10;
    destination.w = 280;
    destination.h = 50;
    destination.y = 280;
    SDL_RenderCopy(renderer, ttuto1, NULL, &destination);
    destination.y = 340;
    SDL_RenderCopy(renderer, ttuto2, NULL, &destination);
    destination.y = 400;
    SDL_RenderCopy(renderer, ttuto3, NULL, &destination);

    surf = TTF_RenderText_Blended(font1, annulation, couleur);
    tannulation = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Blended(font1, annul, couleur);
    tannul = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    SDL_SetRenderDrawColor(renderer, 240, 0, 32, 255);
    destination.y = 480;
    destination.h = 80;
    SDL_RenderFillRect(renderer, &destination);
    SDL_RenderCopy(renderer, tannulation, NULL, &destination);

    SDL_SetRenderDrawColor(renderer, 133, 6, 6, 255);
    destination.y = 600;
    SDL_RenderFillRect(renderer, &destination);
    SDL_RenderCopy(renderer, tannul, NULL, &destination);

    SDL_DestroyTexture(ttuto1);
    SDL_DestroyTexture(ttuto2);
    SDL_DestroyTexture(ttuto3);
    SDL_DestroyTexture(tannulation);
    SDL_DestroyTexture(tannul);
}

void constructbat(SDL_Renderer *renderer, TTF_Font *font1, int type) //type 0 : forreuse, type 1 : usine
{
    int cout[9];
    if (type)
    {
        cout[0] = 50;
        cout[1] = 280;
        cout[2] = 600;
        cout[3] = 1800;
        cout[4] = 5000;
        cout[5] = 9800;
        cout[6] = 15000;
        cout[7] = 22000;
        cout[8] = 45000;
    }
    else
    {
        cout[0] = 10;
        cout[1] = 60;
        cout[2] = 200;
        cout[3] = 650;
        cout[4] = 1230;
        cout[5] = 2400;
        cout[6] = 6000;
        cout[7] = 11500;
        cout[8] = 20000;
    }
    SDL_Rect destination;
    char prix[7];
    SDL_Texture *text;
    SDL_Surface *surf;

    destination.h = 80;
    destination.w = 80;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            destination.x = OFFSETX + 10 + 100 * j;
            destination.y = 280 + 140 * i;
            SDL_RenderFillRect(renderer, &destination);
        }
    }
    destination.h = 40;
    SDL_Color couleur = {255, 228, 54, 255};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sprintf(prix, "%d", cout[3 * i + j]);
            strcat(prix, "$");
            surf = TTF_RenderText_Blended(font1, prix, couleur);
            text = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            destination.x = OFFSETX + 10 + 100 * j;
            destination.w = (int)80.0 * ((float)strlen(prix) / 7);
            destination.h = 40;
            destination.y = 280 + 140 * i + 90;
            SDL_RenderCopy(renderer, text, NULL, &destination);
        }
    }
    SDL_DestroyTexture(text);
    // SDL_FreeSurface(surf); // Deja free dans le for
}

void affichemenu(SDL_Renderer *renderer, int money, TTF_Font *font1, int status)
{
    SDL_Texture *bg[2];
    bg[0] = load_texture_from_image(PATH_BACKGROUND_MENU, renderer);
    bg[1] = load_texture_from_image(PATH_BOUTON_CONSTRUCTION_TUYAU, renderer);
    dessinargent(renderer, font1, money, bg);
    if (status == 1)
    {
        editiontuyaux(renderer, font1);
    }
    if (status == 2)
    {
        constructbat(renderer, font1, 0);
    }
    if (status == 3)
    {
        constructbat(renderer, font1, 1);
    }
    SDL_DestroyTexture(bg[0]);
    SDL_DestroyTexture(bg[1]);
}

/* Deplacement dans fichier event.c -> eventsec
void eventmenu(int posx, int posy, int *status)
{
    if (posy > 750 && posy < 830)
    {
        if (posx > 910 && posx < 990)
        {
            *status = 1;
        }
        if (posx > 1010 && posx < 1090)
        {
            *status = 2;
        }
        if (posx > 1110 && posx < 1190)
        {
            *status = 3;
        }
    }
}
*/