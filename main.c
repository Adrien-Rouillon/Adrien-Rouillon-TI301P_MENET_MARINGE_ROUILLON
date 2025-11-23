#include <stdio.h>
#include "utils.h"
#include "tarjan.h"


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

void testTarjan(){
    t_adjList graph = readGraph("../data/exemple2.txt");
    t_partition part = tarjan(graph);
    print_partition(part);
}

int main() {
    testTarjan();
    return 0;
}

