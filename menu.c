#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

//gcc  menu.c -o prog -lSDL2 -lSDL2_image -lSDL2_ttf

void chargertexture(SDL_Renderer *renderer,SDL_Texture *bg[2])
{
    SDL_Surface *my_image = NULL; 
    my_image = IMG_Load("cosmos.jpeg");
    if (my_image == NULL) printf("my-image is NULL\n");
    bg[0] = SDL_CreateTextureFromSurface(renderer, my_image); 
    my_image = IMG_Load("bouton.png");
    if (my_image == NULL) printf("my-image is NULL\n");
    bg[1]= SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);                                     
    
}

void dessinmenu(SDL_Renderer *renderer, TTF_Font* font1,int offsetx,int offsety, int money, SDL_Texture *bg[2])
{

    char* argent="Argent :";
    SDL_Texture * text;
    SDL_Rect destination,source;
    destination.x=offsetx;
    destination.y=0;
    destination.w=300;
    destination.h=600; //PENSER A CHANGER !!!!!!!!!!!
    SDL_RenderCopy(renderer,bg[0],NULL,&destination);

    SDL_Color couleur  = {9, 106, 9, 255};      
    SDL_Surface * surf     = TTF_RenderText_Blended(font1,argent, couleur);
    text= SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    destination.x=offsetx+20;
    destination.y=25;
    destination.w=260;
    destination.h=100;
    SDL_RenderCopy(renderer,text,NULL,&destination);

    char sous[10];
    sprintf(sous,"%d",money);
    strcat(sous,"$");
    SDL_Color couleur2  = {255, 140, 0, 255};      
    surf     = TTF_RenderText_Blended(font1,sous, couleur2);
    text= SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    destination.y=130;
    destination.w=(int)260.0*((float)strlen(sous)/10);
    SDL_RenderCopy(renderer,text,NULL,&destination);

    source.x=240;
    source.y=60;
    source.h=420;
    source.w=420;
    destination.h=80;
    destination.w=80;
    destination.y=offsety+450;
    for (int k=0;k<3;k++)
    {
        destination.x=10+100*k;
        SDL_RenderCopy(renderer,bg[1],&source,&destination);
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE; 
    }
    SDL_Window   * window;
    int width = 300;
    int height = 600;

    window = SDL_CreateWindow("woaw trop beau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 
            SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) 
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }
    
        if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError()); 
    }

    TTF_Font * font1;
    
    font1 = TTF_OpenFont("arial.ttf", 60 );
    /*int k;
    char *nombre="yo";
    SDL_Texture * text[12];
    for (k=1;k<=11;k++)
    {  
        SDL_Color couleur  = {250, 50, 250, 255};      
        SDL_Surface * surf     = TTF_RenderText_Blended(font1,nombre, couleur);
        text[k]= SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    SDL_Rect destination,source,rect;
    destination.h=45;
    destination.w=45;
    destination.y=10;
    int iW,iH;
    for (k=1;k<12;k++)
    {
        SDL_SetRenderDrawColor(renderer, 50, 250, 50, 255);
        rect.x = 45*k;
        rect.y = 10;
        rect.w = 45;
        rect.h = 45;
        SDL_RenderFillRect(renderer, &rect );
        SDL_QueryTexture(text[k], NULL, NULL, &iW, &iH);
        source.x = 0; source.y = 0;
        source.w = iW; source.h = iH;
        destination.x=45*k;
        SDL_RenderCopy(renderer,text[k],&source,&destination);

    }*/
    SDL_Texture *bg[2] ;
    chargertexture(renderer,bg);
    for (int k=0;k<150;k++)
    {
        dessinmenu(renderer,font1,0,0, k*k,bg);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_CloseFont(font1);
    TTF_Quit();

    SDL_Quit();
    return 0;
}