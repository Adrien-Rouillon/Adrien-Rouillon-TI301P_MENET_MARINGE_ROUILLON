//
// Created by alexa on 13/11/2025.
//

#include "tarjan.h"
#include <stdlib.h>
#include "utils.h"

void add_tarjan(t_tarjanVtl *list, int id, int num, int num_access, int indic) {
    t_tarjanVtx *new = malloc(sizeof(t_tarjanVtx));
    if (id != 0)new->id = id;
    new->temp_num = num;
    new->access_num = num_access;
    new->indic = indic;

}

t_tarjanVtl listAdj_to_Tarjan(t_adjacent_list graph) {
    if (graph.size <= 0) perror("ERROR: listAdj_to_Tarjan");
    t_tarjanVtx * list = malloc(sizeof(t_tarjanVtx)*(graph.size));
    for (int i = 0; i < graph.size; i++) {
        list[i].id = i+1;
        list[i].temp_num = -1;
        list[i].access_num = -1;
        list[i].indic = 0;
    }
    t_tarjanVtl res;
    res.size = graph.size;
    res.summit = list;
    return res;
}