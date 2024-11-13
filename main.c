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

    int x, y;
    int minValue = findMinValueLeaf(map, &x, &y);
    if (x != -1 && y != -1) {
        printf("\nLa valeur minimale de la feuille est a la position (%d, %d) et est egal a %d.\n", x, y, minValue);}
    */return 0;

}
