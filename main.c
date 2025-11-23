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
    t_adjList graph = readGraph("../data/exemple_valid_step3");
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


int main() {
    testcharacteristic();
    return 0;
}

