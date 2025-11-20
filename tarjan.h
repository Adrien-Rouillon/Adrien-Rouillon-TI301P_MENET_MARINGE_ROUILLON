#ifndef INC_2526_TI301_PJT_TARJAN_H
#define INC_2526_TI301_PJT_TARJAN_H
#include "utils.h"

typedef struct s_tarjanVtx { //Vertex
  int id; //identifiant du sommet dans le graphe
  int temp_num; //ordre de découverte
  int access_num; //regrouper les sommets qui communiquent
  int index; //1 si le sommet est dans la pile, 0 sinon
}t_tarjanVtx;

typedef struct s_tarjanVtl { //Verticles
  int size;
  t_tarjanVtx *summit;
} t_tarjanVtl;

typedef struct s_class {
  char *name;
  int *id_summit; //identifiant du sommet dans la classe
  int size;
} t_class;

typedef struct s_partition {
  t_class *classes;
  int nb_classes;
  int size;
}t_partition;

typedef struct s_pile {
  int *elements;
  int size;
}t_pile;

t_tarjanVtx *listAdj_to_Tarjan(t_adjList graph);
void stack_pile(t_pile *pile, int val);
void tarjan_parcour(t_adjList graph, t_tarjanVtx *list, t_pile *pile, t_partition *part, int *count, int index);
t_partition tarjan(t_adjList graph);
void print_partition(t_partition part);

#endif //INC_2526_TI301_PJT_TARJAN_H

/*
void add_tarjan(int id, int num, int num_access, int index) {
t_tarjanVtx *new = malloc(sizeof(t_tarjanVtx));
if (id != 0)new->id = id;
new->temp_num = num;
new->access_num = num_access;
new->index = index;
}
*/