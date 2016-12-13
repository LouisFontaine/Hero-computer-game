/**Fichier principal du jeu*/

#include "main.h"

int main( int argc, char *argv[ ] )
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    // Initialisation de la SDL dans une fonction séparée
    init("H3RO Level editor");

    //Chargement des ressources (graphismes, sons)
    load();

    //Appelle la fonction clean à la fin du programme
    atexit(clean);

    go = 1;
    //Boucle infinie, principale, du jeu
    while (go == 1)
    {

        //On vérifie l'état des entrées (clavier)
        getInput();

        //On affiche tout les éléments
        paint();

        //On met à jour le jeu
        update();

        //Gestion des 60 fps
        //On doit donc attendre 16 ms entre chaque image
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

    }
    exit(0);
}
