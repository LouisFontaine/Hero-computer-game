#include "structs.h"

// Prototypes
extern void paintImage(SDL_Surface *, int, int);
extern void paintTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy);
extern void initializeMonster(int x, int y);
extern void getItem(int itemNumber);
extern void playSoundFx(int type);
extern SDL_Surface *loadImage(char *name);
extern void changeMap(void);
extern void initializePlayer(void);
extern void initPlatform(int x, int y, int type);

//Structures globales utilisées
extern Gestion game;
extern Map map;
extern GameObject Platform[];
extern liste level;
