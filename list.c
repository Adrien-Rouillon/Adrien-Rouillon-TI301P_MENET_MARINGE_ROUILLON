//
// Created by Adrien on 22/10/2025.
//

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

t_cell *create_cell(int summit, float probability) {
    t_cell *cell = malloc(sizeof(t_cell));
    cell->summit = summit;
    cell->probability = probability;
    cell->next = NULL;
    return cell;
}

t_list create_empty_list() {
    t_list list;
    list.head = NULL;
    return list;
}

void add_cell(t_list *list, int summit , float probability){
    t_cell * new = create_cell(summit,probability);
    new->next = list->head;
    list->head = new;
}

void display_list(t_list *list) {
    t_cell *cell = list->head;
    printf("[head @] ->");
    while (cell != NULL) {
        printf("(%d, %.2f) ", cell->summit, cell->probability);
        cell = cell->next;
    }
}

t_adjacent_list create_adj_list(int size) {
    t_adjacent_list list;
    list.size = size;
    list.list = malloc(sizeof(t_cell *) * size);
    for (int i = 0; i < size; i++) {
        list.list[i] = create_empty_list();
    }
    return list;
}

void display_adj_list(t_adjacent_list list) {
    if (list.size == 0) return;
    for (int i = 0; i < list.size; i++) {
        printf("Liste pour le sommet %d: ", i+1);
        display_list(&list.list[i]);
        printf("\n");
    }
}

t_adjacent_list readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, depart, arrivee;
    float proba;
    t_adjacent_list graph;
    if (file==NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    graph = create_adj_list(nbvert);
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
    {
        // on obtient, pour chaque ligne du fichier les valeurs depart, arrivee, et proba
        add_cell(&graph.list[depart-1], arrivee, proba);
    }
    fclose(file);
    return graph;
}


int is_markov_graph(const t_list *adj, int size) {
    int isMarkov = 1;

    for (int i = 0; i < size; i++) {
        float sum = 0.00;
        const t_cell *cell = adj[i].head;
        while (cell) {
            sum += cell->probability;
            cell = cell->next;
        }

        if (sum < 0.99 || sum > 1.00) {
            printf("La somme des probabilités du sommet %d est %.2f\n", i + 1, sum);
            isMarkov = 0;
        }
    }

    if (isMarkov) {
        printf("Le graphe est un graphe de Markov\n");
    }
    else {
        printf("Le graphe n’est pas un graphe de Markov\n");
    }

    return isMarkov;
}