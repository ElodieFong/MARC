#include <malloc.h>
#include <stdlib.h>
#include "tree.h"

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

t_node *findMinValueLeaf(t_node *root) {
    if (root == NULL) return NULL;

    // Cas d'une feuille (pas de fils)
    if (root->nbSons == 0) {
        return root;
    }

    // Sinon, explorer les fils
    t_node *minLeaf = NULL;
    for (int i = 0; i < root->nbSons; i++) {
        t_node *leaf = findMinValueLeaf(root->sons[i]);
        if (leaf != NULL) {
            if (minLeaf == NULL || leaf->val < minLeaf->val) {
                minLeaf = leaf;
            }
        }
    }

    return minLeaf;
}

