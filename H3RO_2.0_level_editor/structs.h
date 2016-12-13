/**Fichier contenant les diff�rentes structures utilis�es pour le jeux*/
#include "defs.h"

/**Structure pour l'input*/
typedef struct Input
{
    int left, right, up, down, add, remove;
    int previous, next, load, save, copy, reinit;
    int mouseX, mouseY;
    int leveldown, levelup;
} Input;

/**Structure utilis�e pour les monstres et le h�ro*/
typedef struct Cursor
{
    int x, y, tileID;
} Cursor;


/**Structure pour g�rer un niveau */
typedef struct Gestion
{
    SDL_Surface *screen;
    int level;
} Gestion;

/**Structure pour repr�senter la map*/
typedef struct Map
{
    SDL_Surface *background, *tileSet;

    /* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonn�es max de fin de la map */
    int maxX, maxY;

    /* Tableau � double dimension repr�sentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];
} Map;
