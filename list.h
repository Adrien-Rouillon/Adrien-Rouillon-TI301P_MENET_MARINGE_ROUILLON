//
// Created by Adrien on 22/10/2025.
//

#ifndef LIST_H
#define LIST_H

#endif //LIST_H

typedef struct s_cell {
    int* summit;
    int probability;
    struct s_cell *next;
}t_cell;

typedef struct s_list{
    t_cell *head;
} t_list;

typedef struct s_adjacent_list {
    int size;
    t_list *list;
}adjacent_list;

t_cell* create_cell(int summit, int probability);
