#include "structs.h"

//Structures globales utilisées
extern GameObject monster[];
extern Gestion game;
extern GameObject player;
extern Map map;
extern GameObject shuriken[];


// Prototypes des fonctions utilisées
extern SDL_Surface *loadImage(char *name);
extern void mapCollision(GameObject *entity);
extern int collide(GameObject *player, GameObject *monster);
extern int checkFall(GameObject monster);
extern void modifyAnimation(GameObject *entity, char *name);
extern void playSoundFx(int type);
extern void monsterCollisionWithMap(GameObject *entity);
