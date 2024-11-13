#include <stdio.h>
#include "map.h"
#include "tree.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    int avail[] = {1, 2};
    t_node *root = createNode(10, 0, 2, avail, 2);
    printf("%d\n", root->val);
    // Créer les sous-arbres
    root->sons[0] = createNode(3, 1, 0, NULL, 0);  // Feuille
    root->sons[1] = createNode(15, 1, 1, NULL, 0);
    root->sons[1]->sons[0] = createNode(7, 2, 0, NULL, 0);  // Feuille

    // Trouver la feuille avec la valeur minimale
    t_node *minLeaf = findMinValueLeaf(root);
    printf("Feuille avec la valeur minimale: %d\n", minLeaf->val);
    t_stack path = chemin (root, minLeaf);
    displayStack(path);
/*
    //  tableau test des coûts de mouvement
    int mvCosts[] = {1, 2, 3, 4, 5}; // Exemple de valeurs de coûts
    int initialMoves[] = {0, 1, 2, 3, 4}; // Exemple de 5 mouvements possibles
    int nbInitialMoves = sizeof(initialMoves) / sizeof(initialMoves[0]);

    // Créer la racine de l'arbre pour la phase
    t_node *root = createNode(0, 0, nbInitialMoves, initialMoves, nbInitialMoves);

    // Construire l'arbre pour la phase de 5 mouvements (ou 4 si case REG)
    int maxDepth = 5;
    creatTree(root, maxDepth, mvCosts);


    // Libérer l'arbre après usage
    freeNode(root);


    */return 0;

}
