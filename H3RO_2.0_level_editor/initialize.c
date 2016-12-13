/**Fichier pour initialiser la SDL et la charger puis pour la libérer*/
#include "initialize.h"

/**Fonction permettant d'initialiser l'editeur*/
void init(char *title)
{
    // Initialise SDL Video si ça ne fonctionne pas, on quitte
    if (SDL_Init(SDL_INIT_VIDEO ) < 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Ouverture de la fenêtre en fonction de la largeur et de la hauteur définies avec le doublebuf pour empêcher le scintillement
    game.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);

    //Sinon on quitte
    if (game.screen == NULL)
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }

    //Nom de la fenêtre
    SDL_WM_SetCaption(title, NULL);

    //Icone
    SDL_WM_SetIcon(SDL_LoadBMP("graphics/icone.bmp"), NULL);

    //Nous mettons le niveau 1 en premier
    game.level = 1;
}

/**Fonction permettant de charger la map et le tileset*/
void load(void)
{
    //Création d'un tableau pour contenir le nom de notre fichier
    char file[120];

    //Si le fond n'est pas chargé, nous le chargeons
    if (game.level == 1) map.background = loadImage("graphics/background1.png");
    if (game.level == 2) map.background = loadImage("graphics/background2.png");
    if (game.level == 3) map.background = loadImage("graphics/background3.png");

    //Sinon on quitte
    if (map.background == NULL)
    {
        printf("Unable to load background");
        exit(1);
    }

    //Nous libérons le précedent tileset et nous chargeons celui correspondant à la map
    if (map.tileSet != NULL) SDL_FreeSurface(map.tileSet);
    sprintf(file, "graphics/tileset%d.png", game.level);
    map.tileSet = loadImage(file);

    if (map.tileSet == NULL)
    {
        printf("Unable to load tileset : %d", game.level);
        exit(1);
    }

    //Nous chargeons la map
    sprintf(file, "map/map%d.txt", game.level);
    loadMap(file);

    if(file == NULL)
    {
        printf("Unable to load map : %d", game.level);
        exit(1);
    }
}

/**Fonction permettant de quitter l'editeur de niveau proprement*/
void clean()
{
    if (map.background != NULL) SDL_FreeSurface(map.background);

    if (map.tileSet != NULL) SDL_FreeSurface(map.tileSet);

    SDL_Quit();
}
