#include "structs.h"

//Structures globales utilisées
extern Gestion game;
extern GameObject player;
extern Input input;
extern Map map;
extern liste level;

//Prototype des fonctions externes que nous allons utiliser
extern SDL_Surface *loadImage(char *name);
extern void centerScrollingOnPlayer(void);
extern void mapCollision(GameObject *entity);
extern void loadMap(char *name);
extern void modifyAnimation(GameObject *entity, char *name);
extern void playSoundFx(int type);
extern void changeMap(void);
extern void createProjectile(void);
