/**Fichier contenant les différentes structures utilisées pour le jeux*/
#include "defs.h"

/**Structure pour l'input*/
typedef struct Input
{
    int left, right, up, down, add, remove;
    int previous, next, load, save, copy, reinit;
    int mouseX, mouseY;
    int leveldown, levelup;
} Input;

/**Structure utilisée pour les monstres et le héro*/
typedef struct Cursor
{
    int x, y, tileID;
} Cursor;


/**Structure pour gérer un niveau */
typedef struct Gestion
{
    SDL_Surface *screen;
    int level;
} Gestion;

/**Structure pour représenter la map*/
typedef struct Map
{
    SDL_Surface *background, *tileSet;

    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonnées max de fin de la map */
    int maxX, maxY;

    /* Tableau à double dimension représentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];
} Map;
