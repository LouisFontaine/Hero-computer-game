#include "structs.h"

// Prototypes des fonctions utilisées
extern void paintMap(void);
extern void paintanimatedplayer(void);
extern void paintObject(GameObject *entity);
extern void paintHud(void);
extern void paintString(char *text, int x, int y, TTF_Font *font);
extern void paintProjectiles(void);
extern void paintPlatform(void);


// Structures globales utilisées
extern Gestion game;
extern Map map;
extern GameObject player;
extern GameObject monster[];
extern TTF_Font *font;

