//
// Created by maely on 12/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

t_node *createNode(int val, int depth, int nb_sons, int *mvCosts, t_move mouvement, t_localisation loc) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node) {
        return NULL; // retourne null si le malloc échoue
    }
    new_node->val = val;
    new_node->depth = depth;
    new_node->nbSons = nb_sons;
    if (nb_sons > 0)
    {
        new_node->sons = (t_node **)malloc(nb_sons * sizeof(t_node *));
        if (!new_node->sons) {
            free(new_node);
            return NULL; // retourne NULL si malloc échoue
        }
        for (int i = 0; i < nb_sons; i++) {
            new_node->sons[i] = NULL;
        }
    }
    else {
        // Noeud feuille
        new_node->sons = NULL;
    }
    new_node->avails = (int *)malloc(nb_sons * sizeof(int));
    if (!new_node->avails) { // libère la mémoire si le malloc échoue
        free(new_node->sons);
        free(new_node);
        return NULL;
    }
    for (int i = 0; i < nb_sons; i++) {
        new_node->avails[i] = mvCosts[i];
    }
    new_node->mouvement = mouvement;
    new_node->loc = loc;
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


void creatTree(t_node *node, int maxDepth, t_move* mouvPoll){
    if (node->depth >= maxDepth){
        return; //s'arreter a la profondeur maxi
    }
    for(int i = 0; i<node->nbSons; i++){
        int cost = node->avails[i];
        int new_cost = cost;
        int *new_avails = malloc((node->nbSons - 1)* sizeof(int)); //nouveau tableau sans la val du noeud
        t_move *newPoll = malloc((node->nbSons - 1)* sizeof(t_move)); //nouveau tableau sans le mouvement du noeud
        int idx = 0;
        //copier les autre mouv dispo sauf le dernier utiliser
        for(int j=0; j<node->nbSons; j++){
            if(j != i){
                new_avails[idx] = node->avails[j];
                newPoll[idx++] = mouvPoll[j];
            }
        }
        if (cost == 0 || cost >= 10000) {
            node->sons[i] = createNode(new_cost, node->depth + 1, 0, NULL, mouvPoll[i], node->loc);
            if (node->sons[i]->sons != NULL) {
                printf("Erreur : un noeud supposé feuille a des fils non NULL\n");
            }
        }
        else
        {
            //créé le noeud suivant
            node->sons[i] = createNode(new_cost, node->depth+1, node->nbSons-1, new_avails, mouvPoll[i], node->loc);
            free(new_avails);
            creatTree(node->sons[i], maxDepth, newPoll);
        }
        free(newPoll);
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
/*


t_node *findMinValueLeaf(t_node *root) {
    if (root == NULL)
        return NULL;
    // Cas d'une feuille
    if (root->nbSons == 0) {
        return root;
    }
    // explorer les fils
    t_node *minLeaf = NULL;
    for (int i = 0; i < root->nbSons; i++) {
        if (root->sons[i] == NULL)
            continue;

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
*/

int is_Path(t_node *root, t_node *node, t_stack *pile) {
    if (root == NULL)
        return 0;
    push(pile, root->mouvement);
    if (root == node) {
        return 1;
    }
    //printf("val du noeud = %d, mouv du noeud = %s\n", root->val, getMoveAsString(root->mouvement));
    for (int i = 0; i < root->nbSons; i++) {
        if(is_Path(root->sons[i], node, pile))
            return 1;
    }
    pop(pile);
    return 0;
}

t_stack chemin (t_node *root, t_node *node_min) {
    t_stack pile = createStack(node_min->depth+1);
    is_Path(root, node_min, &pile);
    int taille = pile.nbElts;
    t_stack stack = createStack(pile.nbElts);
    for (int i = 0; i < taille; i++) {
        t_move mv = pop(&pile);
        push(&stack, mv);
        printf("%s    ", getMoveAsString(mv));
    }
    return stack;
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
    printf("Node (val: %d, depth: %d, nbSons: %d, mouvement: %s, avails: [",
           node->val, node->depth, node->nbSons, getMoveAsString(node->mouvement));

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

