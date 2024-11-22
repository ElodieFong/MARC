//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include "loc.h"
#include "moves.h"
#include "stack.h"

t_localisation loc_init(int x, int y, t_orientation ori)
{
    t_localisation loc;
    loc.pos.x = x;
    loc.pos.y = y;
    loc.ori = ori;
    return loc;
}

int isValidLocalisation(t_position loc, int x_max, int y_max)
{
    return (loc.x >= 0 && loc.x < x_max && loc.y >= 0 && loc.y < y_max);
}

t_position LEFT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x - 1;
    new_pos.y = pos.y;
    return new_pos;
}

t_position RIGHT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x + 1;
    new_pos.y = pos.y;
    return new_pos;
}

t_position UP(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y - 1;
    return new_pos;
}

t_position DOWN(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y + 1;
    return new_pos;
}


/*
//mettre dans un liste les cout associer au mouv - cout de (y-1)
#define MAX_MOVES 100 // Limite arbitraire pour le nombre de positions visitées


void path(t_localisation start, t_stack *mv){
    t_position path[MAX_MOVES];
    int path_length = 0;

    // Ajouter la position de départ au chemin
    path[path_length++] = start.pos;

    // Mettre à jour la localisation avec chaque mouvement de la pile
    t_localisation now = start;

    // Afficher la position de départ
    printf("Path:\n");
    printf("(%d, %d)\n", now.pos.x, now.pos.y);

    // Parcourir les mouvements
    do {
        // Récupérer le prochain mouvement
        t_move mov = pop(mv);
        // Mettre à jour la localisation
        updateLocalisation(&now, mov);
        // Afficher la nouvelle position
        printf("(%d, %d)\n", now.pos.x, now.pos.y);
    }while (mv->nbElts > 0);

    /*do{
        t_move mov = pop(mv); //recup le mouvement
        updateLocalisation(&now, mov); // update la localisation
        path[path_length++] = now.pos;
    }while(mv->nbElts >0);

    // Afficher le chemin parcouru
    printf("Path:\n");
    for (int i = 0; i < path_length; i++) {
    printf("(%d, %d)\n", path[i].x, path[i].y);
    }

    // Libérer la mémoire allouée au tableau
    free(path);
}
*/