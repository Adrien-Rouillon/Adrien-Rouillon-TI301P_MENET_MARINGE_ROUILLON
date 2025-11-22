//
// Created by alexa on 22/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include "utils.h"
#include "tarjan.h"

typedef struct s_matrix {
    int rows;
    int cols;
    float **data;
} t_matrix;

t_matrix create_matrix(int rows, int cols);
void free_matrix(t_matrix matrix);
void display_matrix(t_matrix matrix);

t_matrix adj_list_to_matrix(t_adjList graph);
t_matrix create_empty_matrix(int n);
void copyMatrix(t_matrix destination, t_matrix source);
void multiply_matrix(t_matrix m1, t_matrix m2, t_matrix destination);
float diff_matrix(t_matrix m1, t_matrix m2);

t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);

#endif //INC_2526_TI301_PJT_MATRIX_H