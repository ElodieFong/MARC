//
// Created by maely on 12/11/2024.
//

#ifndef MARC_TREE_H
#define MARC_TREE_H

#include <stdlib.h>
#include "map.h"

// structure d'un noeud
typedef struct s_node{
    int val;
    int depth;
    int nbSons;
    struct s_node **sons;
    int *avails;
    int nbAvails;
} t_node;

//cree noeud
t_node *createNode(int val, int depth, int nb_sons, int *avails, int nbAvails);

//liberer un noeud
void freeNode(t_node *node);

//valeur min d'une feuille
int findMinValueLeaf(t_map map, int* x, int* y);
#endif //MARC_TREE_H
