//
// Created by maely on 12/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "map.h"

t_node *createNode(int val, int depth, int nb_sons, int *mvCosts){
    t_node *new_node = (t_node*)malloc(sizeof(t_node));
    new_node->val = val;
    new_node->depth = depth;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons * sizeof(t_node *));
    for (int i = 0; i < nb_sons; i++) {
        new_node->sons[i] = NULL;
    }
    new_node->avails = mvCosts;
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

void creatTree(t_node *node, int maxDepth, int *choix){
    printf("ca marche, noeud = %d\n", node->val);
    if (node->depth >= maxDepth)
        return; //s'arreter a la profondeur maxi
    for(int i = 0; i<node->nbSons; i++){
        int move = node->avails[i];
        int new_cost = node->val + choix[move];
        int *new_avails = malloc((node->nbSons - 1)* sizeof(int)); //creer les autre mouvement
        int idx = 0;

        //copier les autre mouv dispo sauf le dernier utiliser
        for(int j=0; j<node->nbSons; j++){
            if(node->avails[j] != move){
                new_avails[idx++] = node->avails[j];
            }
        }

        //créé le noeud suivant (l'enfant quoi)
        createNode(new_cost, node->depth+1, node->nbSons-1, new_avails);
        free(new_avails);
        creatTree(node->sons[i], maxDepth, &new_cost);
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



int is_Path(t_node *root, t_node *node, t_stack *pile) {
    if (root == NULL)
        return 0;
    push(pile, root->val);
    if (root == node) {
        return 1;
    }
    for (int i = 0; i < root->nbSons; i++) {
        if(is_Path(root->sons[i], node, pile))
            return 1;
    }
    pop(pile);
    return 0;
}

t_stack chemin (t_node *root, t_node *node_min) {
    t_stack pile = createStack(root->nbSons);
    is_Path(root, node_min, &pile);
    return pile;
}


// fonction affichage crash test

void displayTree(t_node *node, int level) {
    if (node == NULL) {
        return;
    }

    // Indentation pour montrer la hiérarchie
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Affichage des informations du nœud
    printf("Node (val: %d, depth: %d, nbSons: %d, avails: [",
           node->val, node->depth, node->nbSons);

    // Afficher le tableau avails
    for (int i = 0; i < node->nbSons; i++) {
        printf("%d", node->avails[i]);
        if (i < node->nbSons - 1) {
            printf(", ");
        }
    }
    printf("])\n");

    // Parcourir et afficher les fils
    for (int i = 0; i < node->nbSons; i++) {
        displayTree(node->sons[i], level + 1);
    }
}

