 #include "structs.h"

  /* Prototypes des fonctions utilisées */

  extern void init(char *);
  extern void clean(void);
  extern void getInput(void);
  extern void paint(void);
  extern void load(void);
  extern void delay(unsigned int frameLimit);
  extern void update(void);


  /* Déclaration des structures globales utilisées par le game */

  Input input;
  Gestion game;
  Map map;

  /* Ligne à rajouter : */
  Cursor cursor;
