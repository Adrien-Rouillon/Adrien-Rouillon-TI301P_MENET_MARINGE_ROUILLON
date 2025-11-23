#ifndef __HASSE_H__
#define __HASSE_H__
/*
struct t_link_array;
void removeTransitiveLinks(t_link_array *p_link_array);


 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#include "tarjan.h"

typedef struct lien{
	int start;
    int arrive;
}lien;

typedef struct {
	lien *liens;
	int nb_liens;
    int capacite;
}liens;

typedef struct classify{
	int sommet;
    int classe;
}classify;

void initialize_link(liens *container);
void resize_link(liens *container);
int existing_link(int c_dep, int c_arr, liens *container);
void add_link(int c_dep, int c_arr, liens *container);
liens create_diagram_hasse(t_adjList graph, t_partition part);
int find_class_vertex(t_partition part, int summit_id);
void print_diagramme_hasse(liens container, t_partition part);
void free_link(liens *container);
void characteristic(liens containers,t_partition part);
#endif
