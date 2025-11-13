//
// Created by alexa on 13/11/2025.
//

#ifndef INC_2526_TI301_PJT_TARJAN_H
#define INC_2526_TI301_PJT_TARJAN_H
typedef struct s_tarjan {
  int id;
  int num;
  int num_acess;
  int indic;
}t_tarjan;

typedef struct s_class {
  char *name;
  t_tarjan *tarjan;
} t_class;

typedef  t_class *t_tarjan_list;

#endif //INC_2526_TI301_PJT_TARJAN_H