/**Fichier principal du jeu*/

#include "main.h"

int main( int argc, char *argv[ ] )
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    // Initialisation de la SDL dans une fonction s�par�e
    init("H3RO Level editor");

    //Chargement des ressources (graphismes, sons)
    load();

    //Appelle la fonction clean � la fin du programme
    atexit(clean);

    go = 1;
    //Boucle infinie, principale, du jeu
    while (go == 1)
    {

        //On v�rifie l'�tat des entr�es (clavier)
        getInput();

        //On affiche tout les �l�ments
        paint();

        //On met � jour le jeu
        update();

        //Gestion des 60 fps
        //On doit donc attendre 16 ms entre chaque image
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

    }
    exit(0);
}
