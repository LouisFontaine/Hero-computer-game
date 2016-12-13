#include "structs.h"
/* Prototypes des fonctions utilisées */
extern void drawMap(void);
extern void drawanimatedplayer(void);
extern void drawGameObject(GameObject *entity);
extern void drawHud(void);
extern void drawString(char *text, int x, int y, TTF_Font *font);
extern void drawFireballs(void);
extern void drawPlateforme(void);


/* Structures globales */
extern Gestion jeu;
extern Map map;
extern GameObject player;
extern GameObject monster[];
extern TTF_Font *font;

