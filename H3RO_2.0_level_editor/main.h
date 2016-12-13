 #include "structs.h"

  /* Prototypes des fonctions utilis�es */

  extern void init(char *);
  extern void clean(void);
  extern void getInput(void);
  extern void paint(void);
  extern void load(void);
  extern void delay(unsigned int frameLimit);
  extern void update(void);


  /* D�claration des structures globales utilis�es par le game */

  Input input;
  Gestion game;
  Map map;

  /* Ligne � rajouter : */
  Cursor cursor;
