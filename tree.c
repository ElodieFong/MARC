//
// Created by maely on 12/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "map.h"

t_node *createNode(int val, int depth, int nb_sons, int *avails, int nbAvails){
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    new_node->val = val;
    new_node->depth = depth;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons * sizeof(t_node *));
    for (int i = 0; i < nb_sons; i++) {
        new_node->sons[i] = NULL;
    }
    new_node->avails = (int *)malloc(nbAvails * sizeof(int));
    for (int i = 0; i < nbAvails; i++) {
        new_node->avails[i] = avails[i];
    }
    new_node->nbAvails = nbAvails;
    return new_node;
}


void freeNode(t_node *node){
    if (node) {
        for (int i = 0; i < node->nbSons; i++) {
            freeNode(node->sons[i]);
        }
        free(node->sons);
        free(node->avails);
        free(node);
    }
}

void creatTree(t_node *node, int maxDepth, int *mvCosts){
    if (node->depth >= maxDepth)
        return; //s'arreter a la profondeur maxi
    for(int i = 0; i<node->nbAvails; i++){
        int move = node->avails[i];
        int new_cost = node->val + mvCosts[move];
        int *new_avails = malloc((node->nbAvails - 1)* sizeof(int)); //creer les autre mouvement
        int idx = 0;

        //copier les autre mouv dispo sauf le dernier utiliser
        for(int j=0; j<node->nbAvails; j++){
            if(node->avails[j] != move){
                new_avails[idx++] = node->avails[j];
            }
        }

        //créé le noeud suivant (l'enfant quoi)
        createNode(new_cost, node->depth+1, node->nbSons-1, new_avails, node->nbAvails);
        free(new_avails);
        creatTree(node->sons[i], maxDepth, mvCosts);
    }
}

t_node *findMinValueLeaf(t_node *root) {
    if (root == NULL) return NULL;

    // Cas d'une feuille
    if (root->nbSons == 0) {
        return root;
    }

    // explorer les fils
    t_node *minLeaf = NULL;
    for (int i = 0; i < root->nbSons; i++) {
        t_node *leaf = findMinValueLeaf(root->sons[i]);
        if (leaf != NULL) {
            // Si c'est le premier minLeaf ou si on trouve une feuille avec une valeur inférieure
            if (minLeaf == NULL || leaf->val < minLeaf->val) {
                minLeaf = leaf;
            }
        }
    }

    return minLeaf;
}



int isPath(t_node *root, t_node *node, t_stack *pile) {
    if (root == NULL)
        return 0;
    printf(" %d, %d, %d\n", root->val, pile->nbElts, pile->size);
    push(pile, root->val);
    printf("%d, %d, %d\n", root->val, pile->nbElts, pile->size);
    if (root == node) {
        return 1;
    }
    for (int i = 0; i < root->nbSons; i++) {
        if(isPath(root->sons[i], node, pile))
            return 1;
    }
    pop(pile);
    return 0;
}

t_stack chemin (t_node *root, t_node *node_min) {
    t_stack pile = createStack(root->nbSons+2);
    isPath(root, node_min, &pile);
    return pile;
}