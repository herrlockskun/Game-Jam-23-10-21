/*bacground.c*/
/*23 octobre 2021*/
#include <SDL2/SDL_image.h>        
#include <SDL2/SDL.h>
#include "background.h"

/*gcc fade.c -o fade -Wall -Wextra -g -lSDL2 -lSDL2_image */
                                     
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Renderer *renderer )
{
	 SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) printf("my-image %s is NULL\n",file_image_name);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) printf("my-texture is NULL\n");

    return my_texture;  
}

void dessin_texture(int x, int y, int numero_texture, SDL_Texture** tableau_minerai, SDL_Renderer* renderer, int angle, SDL_RendererFlip miroir)
{
	SDL_Rect destination = {0};
	destination.x=x*45;
	destination.y=y*45;
	destination.w=45;
	destination.h=45;
	SDL_Texture* my_texture=tableau_minerai[numero_texture];
	SDL_RenderCopyEx(renderer, my_texture, NULL, &destination,angle, NULL,miroir);
}

int r_angle(int num_tuyau)
{
	int angle=0;
	if (num_tuyau==10 || num_tuyau==3 || num_tuyau==2) angle=270;
	else if (num_tuyau==4 || num_tuyau==11 || num_tuyau==8 ) angle=180;
	else if (num_tuyau==7 || num_tuyau==5 || num_tuyau==6) angle=90;
	return angle;
}

SDL_RendererFlip r_miroir(int num_tuyau)
{
	SDL_RendererFlip miroir  =SDL_FLIP_NONE;
	if (num_tuyau==5 || num_tuyau==8 || num_tuyau==6) miroir=SDL_FLIP_VERTICAL;
	return miroir;
}

int r_numero_texture(int num_tuyau)
{
	int numero_texture;
	if (num_tuyau==0) numero_texture=0;
	else if (num_tuyau==1 || num_tuyau==4 || num_tuyau==7  || num_tuyau==10) numero_texture=1;
	else  numero_texture=2;
	return numero_texture;
}


void dessin_arriere_plan(int carte[20][20], SDL_Renderer* renderer, SDL_Texture** tableau_minerai)
{
//peut être farie une génération aléatopire plsu tard 
	for (int	j=0;j<20;++j)
	{
		for (int	i=0;i<20;++i)
		{
			dessin_texture(i,j,carte[i][j],tableau_minerai,renderer, 0,SDL_FLIP_NONE);
		}
	}
}

/*void dessin_tuyau(tuyau_t * tuyau, SDL_Texture** tableau_minerai, SDL_Renderer* rendeder)
{
	}*/
