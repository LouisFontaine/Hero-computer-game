#include "structs.h"

// Prototypes
extern SDL_Surface *loadImage(char *name);
extern void loadMap(char *name);
extern void closeFont(TTF_Font *font);
extern TTF_Font *loadFont(char *, int);
extern void loadSong(char filename[200] );
extern void loadSound(void);
extern void freeSound(void);
extern void changeMap(void);
extern void loadPlatform(void);
extern void freeListe(void);

// Structures globales utilisées
extern Gestion game;
extern Map map;
extern TTF_Font *font;
extern GameObject player;
extern GameObject monster[MONSTRES_MAX];
extern liste level;
