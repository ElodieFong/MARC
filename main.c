#include <stdio.h>
#include "tree.h"
#include "loc.h"
#include <time.h>

int main() {
    t_map map;
    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    //map = createAleaMap();
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
    //displayMap(map);
    srand(time(NULL));

    //test de mae
    t_localisation marc;
    marc.ori = 1;
    marc.pos.x =1;
    marc.pos.y =1;
    marc = loc_aleatoire(map);
    displayMap(map, marc);
    //fin test de mae

    t_localisation alea = loc_aleatoire(map);
    displayMap(map, alea);
/*
    int avail[] = {1, 2};
    int son[] = {7};
    t_node *root = createNode(10, 0, 2, avail, 7);
    printf("racine = %d\n", root->val);
    // Créer les sous-arbres
    root->sons[0] = createNode(30, 1, 0, NULL, F_20);  // Feuille
    root->sons[1] = createNode(15, 1, 1, son, F_10);
    root->sons[1]->sons[0] = createNode(7, 2, 0, NULL, T_LEFT);  // Feuille

    // Trouver la feuille avec la valeur minimale
    t_node *minLeaf = findMinValueLeaf(root);
    printf("Feuille avec la valeur minimale: %d\n", minLeaf->val);
    t_stack path = chemin (root, minLeaf);
    displayStack(path);

    // fonction affichage crash test debut
    displayTree(root, 0);
    // fonction affichage crash test fin

    //pathfinder(alea, &path);
*/
    //  tableau test des coûts de mouvement
    int initialMoves[] = {1, 3, 2, 4, 5}; // Exemple de 5 mouvements possibles

    // Créer la racine de l'arbre pour la phase
    t_node *root = createNode(1, 2, 3, initialMoves, NOTHING, marc);

    // Construire l'arbre pour la phase de 5 mouvements (ou 4 si case REG)
    int maxDepth = 5;
    t_move poll[] = { T_LEFT, F_20, F_30, F_10, T_RIGHT};
    creatTree(root, maxDepth, poll);

    displayTree(root, 0);
    t_node *min = findMinValueLeaf(root);
    printf("Feuille avec la valeur minimale: %d\n", min->val);
    t_stack path = chemin (root, min);
    displayStack(path);
    pathfinder(alea, &path);
    // Libérer l'arbre après usage
    freeNode(root);

    //t_localisation loc = loc_init(0, 0, NORTH); // Start at (0, 0) facing NORTH

    resetMoveAvailabilities();
    mouvPoll(3);

    return 0;

}
