#include "structs.h"

// Prototypes
extern void init(char *);
extern void clean(void);
extern void getInput(void);
extern void paint(void);
extern void load(void);
extern void delay(unsigned int frameLimit);
extern void update(void);


// D�claration des structures globales utilis�es par le jeu
Input input;
Gestion game;
Map map;
Cursor cursor;
