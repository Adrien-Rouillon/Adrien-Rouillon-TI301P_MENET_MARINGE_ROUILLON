//
// Created by alexa on 13/11/2025.
//

#include "tarjan.h"

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

t_tarjanVtx *listAdj_to_Tarjan(t_adjList graph) {
    if (graph.size <= 0) perror("ERROR: listAdj_to_Tarjan");
    t_tarjanVtx * list = malloc(sizeof(t_tarjanVtx)*(graph.size));
    for (int i = 0; i < graph.size; i++) {
        list[i].id = i+1;
        list[i].temp_num = -1;
        list[i].access_num = -1;
        list[i].index = 0;
    }
    return list;
}

void stack_pile(t_pile *pile, int val) {
    pile->elements[pile->size] = val;
    pile->size++;
}

void tarjan_parcour(t_adjList graph, t_tarjanVtx *list, t_pile *pile, t_partition *part, int *count, int index) {
    t_tarjanVtx *curSummit = &list[index];
    curSummit->access_num = *count;
    curSummit->temp_num = *count;
    (*count)++;
    stack_pile(pile, curSummit->id);
    curSummit->index = 1;
    t_cell *cell = graph.list[index].head;
    while (cell) {
        if (list[cell->summit].temp_num == -1) {
            tarjan_parcour(graph, list, pile, part, count, cell->summit);
        } else if (list[cell->summit].index == 1) {
            if (list[cell->summit].access_num < curSummit->access_num) {
                curSummit->access_num = list[cell->summit].access_num;
            }
        }
        cell = cell->next;
    }
    if (curSummit->temp_num == curSummit->access_num) {
        t_class newClass;
        newClass.size = 0;
        newClass.id_summit = malloc(sizeof(int) * graph.size);
        int idSummitUnpile;
        do {
            if (pile->size <= 0) {
                perror("ERROR: stack_pile");
                exit(EXIT_FAILURE);
            }
            idSummitUnpile = pile->elements[pile->size - 1];
            pile->size--;
            t_tarjanVtx *summitUnpile = &list[idSummitUnpile - 1];
            summitUnpile->index = 2;
            newClass.id_summit[newClass.size++] = idSummitUnpile;
        } while (idSummitUnpile != curSummit->id);
        part->classes[part->size] = newClass;
        part->size++;
    }
}

t_partition tarjan(t_adjList graph) {
    t_partition part;
    part.classes = malloc(sizeof(t_class) * graph.size);
    part.size = 0;
    t_tarjanVtx *list = malloc(sizeof(t_tarjanVtx) * graph.size);
    for (int i = 0; i < graph.size; i++) {
        list[i].id = i + 1;
        list[i].temp_num = -1;
        list[i].access_num = -1;
        list[i].index = 0;
    }
    t_pile pile;
    pile.elements = malloc(sizeof(int) * graph.size);
    pile.size = 0;
    int count = 0;
    for (int i = 0; i < graph.size; i++) {
        if (list[i].temp_num == -1) {
            tarjan_parcour(graph, list, &pile, &part, &count, i);
        }
    }
    free(list);
    free(pile.elements);
    return part;
}

void print_partition(t_partition part) {
    for (int i = 0; i < part.size; i++) {
        printf("Composante C%d: {", i + 1);
        for (int j = 0; j < part.classes[i].size; j++) {
            printf("%d", part.classes[i].id_summit[j]);
            if (j < part.classes[i].size - 1) {
                printf(",");
            }
        }
        printf("}\n");
    }
}
