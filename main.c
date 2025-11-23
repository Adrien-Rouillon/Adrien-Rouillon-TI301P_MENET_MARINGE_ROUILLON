#include <stdio.h>
#include "utils.h"
#include "tarjan.h"
#include "hasse.h"
#include "matrix.h"


void testMarkov(){
    t_adjList graph = readGraph("../data/exemple1.txt");
    display_adj_list(graph);
    printf("\n");
    is_markov_graph(graph);
}

void testConvertisseurMermaidChart(){
    t_diagram diag = createDiagram("../data/exemple1_from_chatGPT.txt");
    writeDiagram(diag, "../data/exemple2_chatGPT_fixed.mmd");
}

// test de Tarjan
void testTarjan(){
    t_adjList graph = readGraph("../data/exemple2.txt");
    t_partition part = tarjan(graph);
    print_partition(part);
}
void TestHasse() {
    t_adjList graph = readGraph("../data/exemple3.txt");
    t_partition part = tarjan(graph);
    liens hasse = create_diagram_hasse(graph, part);
    print_diagramme_hasse(hasse, part);
    free_link(&hasse);
}
void testcharacteristic() {
    t_adjList graph = readGraph("../data/exemple3.txt");
    t_partition part = tarjan(graph);
    liens hasse = create_diagram_hasse(graph, part);
    characteristic(hasse,part);
    print_diagramme_hasse(hasse, part);
    free_link(&hasse);
}

// test de matrice
void testMatrix() {
    // test pour charger et convertir une matrice M
    t_adjList graph = readGraph("../data/exemple1.txt"); // Ou exemple1.txt
    t_matrix M = adj_list_to_matrix(graph);
    printf("Matrice d'adjacence (M) :\n");
    print_matrix(M);

    // test pour tester la multiplication d'une matrice M2
    t_matrix M2 = create_empty_matrix(M.rows);
    multiply_matrix(M, M, M2);
    printf("\nMatrice au carre (M^2) :\n");
    print_matrix(M2);

    // test pour extraire une sous-matrice avec Tarjan
    t_partition part = tarjan(graph);
    if (part.size > 0) {
        printf("\nSous-matrice pour la premiere composante (%s) :\n", part.classes[0].name);
        t_matrix sub = subMatrix(M, part, 0);
        print_matrix(sub);
        free_matrix(sub);
    }

    free_matrix(M);
    free_matrix(M2);
}

void testPartie3() {
    // étape 1
    t_adjList graph = readGraph("../data/exemple_meteo.txt");
    t_matrix M = adj_list_to_matrix(graph);
    // M_pow qui accumule les multiplications
    t_matrix M_pow = create_empty_matrix(M.rows);
    t_matrix M_temp = create_empty_matrix(M.rows);
    copy_matrix(M_pow, M);

    printf("Matrice M initiale :\n");
    print_matrix(M);
    // boucle pour calculer M^2 jusqu'à M^7
    for (int i = 2; i <= 7; i++) {
        multiply_matrix(M_pow, M, M_temp);
        copy_matrix(M_pow, M_temp);

        // affichage seulement si on est au jour 3 ou 7
        if (i == 3 || i == 7) {
            printf("\nMatrice M^%d (Jour %d)\n", i, i);
            print_matrix(M_pow);
        }
    }
    // calcul de la convergence M^n
    int n = 7;
    float diff = 1.0;
    while (diff > 0.01 && n < 1000) {
        copy_matrix(M_temp, M_pow);
        multiply_matrix(M_temp, M, M_pow);
        diff = diff_matrix(M_pow, M_temp);
        n++;
    }
    printf("\nConvergence atteinte a n=%d (Etat Stable) :\n", n);
    print_matrix(M_pow);

    // étape 2
    t_adjList graph2 = readGraph("../data/exemple2.txt");
    t_matrix M2 = adj_list_to_matrix(graph2);
    t_partition part = tarjan(graph2);

    printf("\nDistributions par classes :\n");
    for (int i = 0; i < part.size; i++) {
        // isolation la classe et calcule de la convergence
        t_matrix sub = subMatrix(M2, part, i);

        // recréer des matrices locales
        t_matrix sub_res = create_empty_matrix(sub.rows);
        t_matrix sub_tmp = create_empty_matrix(sub.rows);
        copy_matrix(sub_res, sub);

        diff = 1.0;
        while (diff > 0.01) {
            copy_matrix(sub_tmp, sub_res);
            multiply_matrix(sub_tmp, sub, sub_res);
            diff = diff_matrix(sub_res, sub_tmp);
        }
        printf("Classe %s : \n", part.classes[i].name);
        print_matrix(sub_res);

        free_matrix(sub); free_matrix(sub_res); free_matrix(sub_tmp);
    }
    free_matrix(M); free_matrix(M2);
    free_matrix(M_pow); free_matrix(M_temp);
}

int main() {
    testPartie3();
    return 0;
}

