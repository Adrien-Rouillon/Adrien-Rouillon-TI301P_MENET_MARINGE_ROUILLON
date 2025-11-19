//
// Created by alexa on 13/11/2025.
//

#include "tarjan.h"
#include <stdlib.h>
#include "utils.h"

void add_tarjan(t_tarjan_list *list, int id, int num, int num_access, int indic) {
    t_tarjan *new = malloc(sizeof(t_tarjan));
    if (id != 0)new->id = id;
    new->temp_num = num;
    new->access_num = num_access;
    new->indic = indic;

}

t_tarjan_list listAdj_to_Tarjan(t_adjacent_list graph) {
    t_tarjan_list list = malloc(sizeof(t_class));
    if (graph.size == 0) list->size;
    for (int i = 0; i < graph.size; i++) {
        const t_cell *cell = graph.list[i].head;
        while (cell) {
            t_tarjan *new = malloc(sizeof(t_tarjan));
            cell = cell->next;
        }
    }
}