/*bacground.c*/
/*23 octobre 2021*/
#include "background.h"

/*gcc fade.c -o fade -Wall -Wextra -g -lSDL2 -lSDL2_image */

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Renderer *renderer)
{
	SDL_Surface *my_image = NULL;	// Variable de passage
	SDL_Texture *my_texture = NULL; // La texture

	my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
										  // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
										  // uniquement possible si l'image est au format bmp */
	if (my_image == NULL)
		printf("my-image %s is NULL\n", file_image_name);

	my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
	SDL_FreeSurface(my_image);									   // la SDL_Surface ne sert que comme élément transitoire
	if (my_texture == NULL)
		printf("my-texture is NULL\n");

	return my_texture;
}

void dessin_texture(int x, int y, int numero_texture, SDL_Texture **tableau_minerai, SDL_Renderer *renderer, int angle, SDL_RendererFlip miroir)
{
	SDL_Rect destination = {0};
	destination.x = x * 45;
	destination.y = y * 45;
	destination.w = 45;
	destination.h = 45;
	SDL_Texture *my_texture = tableau_minerai[numero_texture];
	SDL_RenderCopyEx(renderer, my_texture, NULL, &destination, angle, NULL, miroir);
}

int r_angle(int num_tuyau)
{
	int angle = 0;
	// if (num_tuyau == 10 || num_tuyau == 5 || num_tuyau == 2)
	// 	angle = 270;
	// else if (num_tuyau == 4 || num_tuyau == 11 || num_tuyau == 8) //6
	// 	angle = 180;
	// else if (num_tuyau == 7 || num_tuyau == 4 || num_tuyau == 6 || num_tuyau == 3)
	// 	angle = 90;

	switch (num_tuyau)
	{
	case 3:	 // bas_droite
	case 10: // droite
	case 2:	 // bas_gauche
		angle = 270;
		break;
	case 12: // droite_bas
	case 11: // droite_haut
	case 4:	 // haut
		angle = 180;
		break;
	case 5: // haut_gauche
	case 7: // gauche
	case 6: // haut_droite
		angle = 90;
		break;

	default:
		break;
	}

	return angle;
}

SDL_RendererFlip r_miroir(int num_tuyau)
{
	SDL_RendererFlip miroir = SDL_FLIP_NONE;
	// if (num_tuyau == 5 || num_tuyau == 8 || num_tuyau == 6)
	// 	// if (num_tuyau == 12 || num_tuyau == 6 || num_tuyau == 2 || num_tuyau == 8)
	// 	miroir = SDL_FLIP_VERTICAL;
	switch (num_tuyau)
	{
	case 6:	 // haut_droite
	case 8:	 // gauche_haut
	case 12: // doite_bas
	case 2:	 // bas_gauche
		miroir = SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}
	return miroir;
}

int r_numero_texture(int num_tuyau)
{
	int numero_texture;
	if (num_tuyau == 0)
		numero_texture = 0;
	else if (num_tuyau == 1 || num_tuyau == 4 || num_tuyau == 7 || num_tuyau == 10)
		numero_texture = 1;
	else
		numero_texture = 2;
	return numero_texture;
}

void dessin_arriere_plan(int carte[20][20], SDL_Renderer *renderer, SDL_Texture **tableau_minerai)
{
	//peut être farie une génération aléatopire plsu tard
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			dessin_texture(i, j, carte[i][j], tableau_minerai, renderer, 0, SDL_FLIP_NONE);
		}
	}
}

void dessin_tuyau(listeTuyau_t *tuyau_l,
				  SDL_Texture **tableau_minerai,
				  SDL_Renderer *renderer)
{
	int nb_tuyau = tuyau_l->taille;
	int num_tuyau, x, y, angle, numero_texture, taille;
	SDL_RendererFlip miroir;
	for (int j = 0; j < nb_tuyau; j++)
	{
		taille = tuyau_l->liste[j]->taille;
		for (int i = 0; i < taille; i++)
		{
			x = tuyau_l->liste[j]->lien_contenu_case[i][0];
			y = tuyau_l->liste[j]->lien_contenu_case[i][1];
			num_tuyau = tuyau_l->liste[j]->orientation[i];
			angle = r_angle(num_tuyau);
			numero_texture = r_numero_texture(num_tuyau);
			miroir = r_miroir(num_tuyau);
			dessin_texture(x, y, numero_texture, tableau_minerai, renderer, angle, miroir);
		}
	}
}
