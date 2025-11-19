#ifndef INC_2526_TI301_PJT_TARJAN_H
#define INC_2526_TI301_PJT_TARJAN_H
typedef struct s_tarjanVtx { //Vertex
  int id; //indentifiant du sommet dans le graphe
  int temp_num; //ordre de découverte
  int access_num; //regrouper les sommets qui communiquent
  int indic; //1 si le sommet est dans la pile, 0 sinon
}t_tarjanVtx;

typedef struct s_tarjanVtl { //Verticles
  int size;
  t_tarjanVtx *summit;
} t_tarjanVtl;

typedef struct s_class {
  char *name;
  int *id_summit; //indentifiant du sommet dans la classe
  int size;
} t_class;

typedef struct s_partition {
  t_class *classes;
  int nb_classes;
}t_partition;

typedef struct s_pile {
  int *elements;
  int size;
};

#endif //INC_2526_TI301_PJT_TARJAN_H