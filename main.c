#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


void test1(){
    t_adjacent_list graph = readGraph("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple1_chatGPT_fixed.txt");
    display_adj_list(graph);
    printf("\n");
    is_markov_graph(graph);
}


void test2() {
    t_diagram diag = createDiagram("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple_valid_step3.txt");
    writeDiagram(diag, "C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/test.txt");
}

int main() {
    t_diagram diag = createDiagram("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple_valid_step3.txt");
    writeDiagram(diag, "C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/test.txt");
    return 0;
}

