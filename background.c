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
    if (my_image == NULL) printf("my-image is NULL\n");

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) printf("my-texture is NULL\n");

    return my_texture;  
}

void minerais(int x, int y, int numero_minerai, SDL_Texture** tableau_minerai, SDL_Renderer* renderer)
{
	SDL_Rect destination = {0};
	destination.x=x*45;
	destination.y=y*45;
	destination.w=45;
	destination.h=45;
	SDL_Texture* my_texture=tableau_minerai[numero_minerai];
	SDL_RenderCopy(renderer, my_texture, NULL, &destination);
}

void dessin_arriere_plan(int carte[20][20], SDL_Renderer* renderer, SDL_Texture** tableau_minerai)
{
//peut être farie une génération aléatopire plsu tard 
	for (int	j=0;j<20;++j)
	{
		for (int	i=0;i<20;++i)
		{
			minerais(i,j,0,tableau_minerai,renderer);
		}
	}
}
