#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tarjan.h"


void test1(){
    t_adjList graph = readGraph("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple1_chatGPT_fixed.txt");
    display_adj_list(graph);
    printf("\n");
    is_markov_graph(graph);
}

void test2(){
    t_diagram diag = createDiagram("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple2_chatGPT_fixed.txt");
    writeDiagram(diag, "C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple2_chatGPT_fixed.mmd");
}

int main() {
    t_adjList graph = readGraph("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple2.txt");
    t_partition part = tarjan(graph);
    print_partition(part);
    return 0;
}

