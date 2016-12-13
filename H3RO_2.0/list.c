#include "list.h"

liste new_singleton(int c) ///création d'un maillon de la liste
{
    liste l = malloc(sizeof(node));
    l->info = c;
    l->glob = 0;
    l->succ = NULL;
    return l;
}

liste create_list(int c) ///création d'une liste
{
    int i = 1;
    liste l = NULL;
    liste cour = NULL;
    liste prec = NULL;
    if(!l)
    {
        l = new_singleton(i);
        prec = l;
    }
    for(i = 2; i <= c; i++)
    {
        cour = new_singleton(i);
        prec->succ = cour;
        prec = cour;
    }
    cour->succ = new_singleton(0);
    cour = cour->succ;
    cour->glob = LEVEL_MAX + 1;
    return l;
}
/**Libere la liste (imposzssible de faire en récursive car la liste est déclarée comme
une variable globale*/
void freeListe()
{
    int i;
    liste tmp = level;
    for(i = 0; i < 3*LEVEL_MAX;i++)
    {
        tmp = level->succ;
        free(level);
        level = tmp;
    }
}
