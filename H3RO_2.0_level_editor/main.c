#include "main.h"

int main( int argc, char *argv[ ] )
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    /* Initialisation de la SDL dans une fonction s�par�e (voir apr�s) */
    init("H3RO Level editor");

    /* Chargement des ressources (graphismes, sons) */
    load();

    /* Appelle la fonction clean � la fin du programme */
    atexit(clean);

    go = 1;


    /* Boucle infinie, principale, du jeu */

    while (go == 1)
    {

        /* On v�rifie l'�tat des entr�es (clavier puis plus tard joystick */
        getInput();

        /* On affiche tout */
        paint();

         /* On met � jour le jeu */
        update();

        /* Gestion des 60 fps ( 60 images pas seconde : soit 1s ->1000ms/60 = 16.6 -> 16
        On doit donc attendre 16 ms entre chaque image (frame) */
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

    }

    /* Exit */
    exit(0);

}
