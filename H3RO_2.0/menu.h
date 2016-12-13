#include "structs.h"

// Structures globales utilisées
extern Gestion game;
extern TTF_Font *font;
extern Input input;
extern GameObject player;

// Prototypes
extern void paintString(char *text, int x, int y, TTF_Font *font);
extern void changeMap(void);
extern void initializePlayer(void);
extern void paintImage(SDL_Surface *, int, int);
