# Projet_L2_2.0
Projet de programmation réalisé au cours d'une deuxième année du cycle préparatoire à l'EFREI.

Afin de compiler le programme, il faut installer la SDL, SDL_TTF, SDL_mixer.

Pour cela il faut tout d'abord télécharger et extraire le dossier disponible en cliquant sur le lien suivant : https://github.com/gusfl/Compilateurs-C-EFREI/archive/gcc-4.9.zip

Ensuite (sous codeblocks), aller dans "Settings" puis dans "compiler..." :

   Dans l'onglet "Toolchain executables", pour "Compiler's installation directory", sélectionner l'emplacement du dossier téléchargé à l'endroit où vous l'avez décompressé.

   Dans l'onglet "Linker settings", Dans la fenêtre "Other linker options", copier-coller le texte suivant :

-lmingw32 -lSDLmain -lSDL -lm -lSDL_image -lSDL_net -lSDL_gfx -lSDL_mixer -lSDL_ttf

Le code peut maintenant être compilé sans problème.
