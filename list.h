//
// Created by Adrien on 22/10/2025.
//

#ifndef LIST_H
#define LIST_H

#endif //LIST_H

typedef struct s_cell {
    int summit;
    float probability;
    struct s_cell *next;
} t_cell;

typedef struct s_list{
    t_cell *head;
} t_list;

typedef struct s_adjacent_list {
    int size;
    t_list *list;
} t_adjacent_list;

t_cell *create_cell(int summit, float probability);

t_list create_empty_list();

void add_cell(t_list *mylist, int summit , float probability);

void display_list(t_list *list);

t_adjacent_list create_adj_list(int size);

void display_adj_list(t_adjacent_list list);

t_adjacent_list readGraph (const char *filename);
