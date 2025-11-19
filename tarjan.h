#ifndef INC_2526_TI301_PJT_TARJAN_H
#define INC_2526_TI301_PJT_TARJAN_H
typedef struct s_tarjanV {
  int id;
  int temp_num;
  int access_num;
  int indic;
}t_tarjan;

typedef struct s_tarjanVertices {
  int size;
  t_tarjan *summit;
} t_tarjan_vtl;

typedef struct s_class {
  char *name;
  int *id_summit;
  int size;
} t_class;

typedef  t_tarjan_vtl *t_tarjan_list;

#endif //INC_2526_TI301_PJT_TARJAN_H