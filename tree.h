//
// Created by maely on 12/11/2024.
//

#ifndef MARC_TREE_H
#define MARC_TREE_H

#include <stdlib.h>
#include "map.h"
#include "stack.h"
#include "moves.h"

// structure d'un noeud
typedef struct s_node{
    int val;
    int depth;
    int nbSons;
    struct s_node **sons;
    int *avails;
    t_move mouvement;
} t_node;

//cree noeud
t_node *createNode(int val, int depth, int nb_sons, int *avails, t_move mouvement);

//liberer un noeud
void freeNode(t_node *node);

//creer l'arbre
void creatTree(t_node *node, int maxDepth, t_move* mouvPoll);

//valeur min d'une feuille
t_node *findMinValueLeaf(t_node *root);

//cherche un chemin
int is_Path(t_node *root, t_node *node, t_stack *pile);

//chemin de la racine vers la feuille de valeur minimale
t_stack chemin (t_node *node, t_node *node_min);
#endif //MARC_TREE_H

// fonction affichage crash test
void displayTree(t_node *node, int level);
