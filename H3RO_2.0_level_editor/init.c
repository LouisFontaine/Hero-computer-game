#include "init.h"

/* Fonction qui initialise le jeu */

void init(char *title)
{

    /* Initialise SDL Video. Si la valeur de retour est inférieure à zéro, la SDL n'a pas pu
     s'initialiser et on quite */

    if (SDL_Init(SDL_INIT_VIDEO ) < 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }


     /* On crée la fenêtre, représentée par le pointeur jeu.screen en utilisant la largeur et la
     hauteur définies dans les defines (defs.h). On utilise aussi la mémoire vidéo
     (SDL_HWPALETTE) et le double buffer pour éviter que ça scintille
     (SDL_DOUBLEBUF) */

    jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);

     /* Si on y arrive pas, on quitte */

    if (jeu.screen == NULL)
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH,
                     SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }

    /* On entre le titre de la fenêtre */

    SDL_WM_SetCaption(title, NULL);

    SDL_WM_SetIcon(SDL_LoadBMP("graphics/icone.bmp"), NULL);

    //On commence par le level 1
    jeu.level = 1;

}

void loadGame(void)
{
    //On crée un tableau de 120 caractères pour contenir le nom de notre fichier
    char file[120];

    /* Si le background est déjà chargé, on ne le recharge pas */
    if (map.background == NULL)
        map.background = loadImage("graphics/background.png");

    /* si on ne peut pas, on quitte */
    if (map.background == NULL)
    {
        printf("Unable to load background");
        exit(1);
    }

    //On décharge le tileset précédent et on charge celui de la map, si nécessaire
    if (map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }

    sprintf(file, "graphics/tileset%d.png", jeu.level);
    map.tileSet = loadImage(file);

    if (map.tileSet == NULL)
    {
        printf("Unable to load tileset : %d", jeu.level);
        exit(1);
    }


    /* On charge la map */
    sprintf(file, "map/map%d.txt", jeu.level);
    loadMap(file);

    if(file == NULL)
    {
        printf("Unable to load map : %d", jeu.level);
        exit(1);
    }
}

/* Fonction qui quitte le jeu proprement */

void cleanup()
{
    if (map.background != NULL)
    {
        SDL_FreeSurface(map.background);
    }

    /* Libère l'image du tileset */

    if (map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }

    /* Quitte la SDL */
    SDL_Quit();
}
