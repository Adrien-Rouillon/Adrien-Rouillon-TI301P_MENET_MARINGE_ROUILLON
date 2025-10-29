//
// Created by Adrien on 22/10/2025.
//

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

t_cell create_cell(int summit, int probability) {
    t_cell cell;
    cell.summit = summit;
    cell.probability = probability;
    cell.next = NULL;
    return cell;
}

void add_cell(t_list *mylist, int summit , int probability){
    t_cell * new = create_cell(summit,probability);
    new->next = mylist->head;
    mylist->head = new;
}

/*
t_list* create_empty_list(){
    t_list* list;
}
t_list create_empty_list() {
    t_list list;
    list.head = NULL;
    return list;
}
*/

void display_list(t_list *list) {
    t_cell *cell = list->head;
    printf("Liste pour le somet 1: [head @] ->");
    while (cell != NULL) {
        printf("(%d, %d) ", cell->summit, cell->probability);
        cell = cell->next;
    }

}