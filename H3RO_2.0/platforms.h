#include "structs.h"

// Structures globales utilisées
extern Gestion game;
extern Map map;
extern struct GameObject Platform[];
extern GameObject player;

// Fonctions utilisées
extern void paintImage(SDL_Surface *image, int x, int y);
extern SDL_Surface *loadImage(char *name);
