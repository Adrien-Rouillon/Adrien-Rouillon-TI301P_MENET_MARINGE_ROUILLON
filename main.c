#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main() {
    t_adjacent_list graph = readGraph("C:/Users/Adrien/CLionProjects/P2/Adrien-Rouillon-TI301P_MENET_MARINGE_ROUILLON/data/exemple1.txt");
    display_adj_list(graph);
    return 0;
}

