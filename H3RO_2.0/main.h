#include "structs.h"

// Prototypes

extern void initialize(char *);
extern void clean(void);
extern void getInput(void);
extern void paint(void);
extern void load(void);
extern void delay(unsigned int);
extern void renewPlayer(void);
extern void initializePlayer(void);
extern void renewMonsters(void);
extern void paintStartMenu(void);
extern void renewStartMenu(void);
extern void paintImage(SDL_Surface *image, int x, int y);
extern void paintPauseMenu(void);
extern void renewPauseMenu(void);
extern void paintMap(void);
extern void paintObject(GameObject *entity);
extern void paintHud(void);
extern void doProjectiles(void);
extern void paintProjectiles(void);
extern void doPlatform(void);
extern void paintPlatform(void);
extern void renewEndMenu(void);
extern void paintEndMenu(void);
extern liste create_list(int);
extern void init_list_map(liste);
extern void verifyPowerUp(int);


//Déclaration des structures globales utilisées par le jeu

Input input;
Gestion game;
Map map;
GameObject player;
GameObject monster[MONSTRES_MAX];
GameObject shuriken[10];
GameObject Platform[50];
liste level = NULL;

//Déclaration de la police de carractère
TTF_Font *font;
