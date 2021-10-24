/*main.c*/
#include "main.h"

int main()
{
   if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
       // Initialisation de SDL_Mixer
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1; 
    }   

/*    Mix_Music* music = Mix_LoadMUS("musique-dascenseur.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
    
    Mix_Music* music_vie = Mix_LoadMUS("vie.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
   
    Mix_Music* music_mort = Mix_LoadMUS("mort.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
    Mix_PlayMusic(music, -1); // Joue notre musique   

*/
    SDL_Window *window;
    int width = 1200;
    int height =900;
    int taille = 0;
	int running=1;
	

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_SetWindowTitle(window, "Lunaire");
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

int carte[20][20];

for (int j=0;j<20;++j)
{
	for (int i=0;i<20;++i)
	{
		carte[i][j]=0;
	}
}


	SDL_Texture** tableau_minerai =malloc(10*sizeof(SDL_Texture *));
	tableau_minerai[0]=load_texture_from_image("lune.jpg", renderer );
	tableau_minerai[1]= load_texture_from_image("horizontale.png", renderer );
	tableau_minerai[2]= load_texture_from_image("virage_2.png", renderer );
	
	dessin_arriere_plan(carte, renderer, tableau_minerai);
	/*tuyau en dur*/

	listeTuyau_t  *l_tuyau;;
	initListeTuyau(&l_tuyau);
	initTuyau(&l_tuyau);
	l_tuyau->liste[l_tuyau->taille-1]->lien_contenu_case[0][0]=0;
	l_tuyau->liste[l_tuyau->taille-1]->lien_contenu_case[0][1]=1;
	l_tuyau->liste[l_tuyau->taille-1]->orientation[0]=1;
	l_tuyau->liste[l_tuyau->taille-1]->taille=1;
	dessin_tuyau(l_tuyau,tableau_minerai,renderer);
	
/*	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,r_angle(1), r_miroir(1));
	dessin_texture(0,1,r_numero_texture(3),tableau_minerai,renderer,r_angle(3), r_miroir(3));
	dessin_texture(1,1,r_numero_texture(11),tableau_minerai,renderer,r_angle(11), r_miroir(11));
	dessin_texture(1,0,r_numero_texture(6),tableau_minerai,renderer,r_angle(6), r_miroir(6));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
  */  SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    running = 0;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    width = event.window.data1;
                    height = event.window.data2;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    break;
                }
                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        

    	SDL_RenderPresent(renderer);
        SDL_Delay(17);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
