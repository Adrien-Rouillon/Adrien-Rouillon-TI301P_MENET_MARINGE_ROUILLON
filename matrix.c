#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tarjan.h"
#include "utils.h"

// créer une matrice et allouer la mémoire
t_matrix create_matrix(int rows, int cols) {
    t_matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = malloc(sizeof(float*) *rows);
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = malloc(sizeof(float) * cols);
        for (int j = 0; j < cols; j++) {
            matrix.data[i][j] = 0;
        }
    }
    return matrix;
}

// libérer la mémoire d'une matrice
void free_matrix(t_matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}

// créer une matrice n x n remplie de 0
t_matrix create_empty_matrix(int n) {
    return create_matrix(n, n);
}

// convertir la liste adjacente vers la matrice
t_matrix adj_list_to_matrix(t_adjList graph) {
    t_matrix matrix = create_matrix(graph.size, graph.size);
    for (int i = 0; i < graph.size; i++) {
        t_cell *current = graph.list[i].head;
        while (current != NULL) {
            if (current -> summit - 1 < graph.size) {
                matrix.data[i][current->summit - 1] = current-> probability;
            }
            current = current->next;
        }
    }
    return matrix;
}

// copier une matrice
void copy_matrix(t_matrix destination, t_matrix source) {
    if (destination.rows != source.rows || destination.cols != source.cols) {
        printf("Erreur : les dimmensions sont incompatibles pour la copie\n");
        return;
    }
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            destination.data[i][j] = source.data[i][j];
        }
    }
}

// multiplication de matrices m1 x m2
void multiply_matrix(t_matrix m1, t_matrix m2, t_matrix destination) {
    if (m1.cols != m2.rows) {
        printf("Erreur : les dimensions sont incompatibles pour la multiplication");
        return;
    }
    for (int i=0; i<destination.rows; i++) {
        for (int j=0; j<destination.cols; j++) {
            destination.data[i][j] = 0;
        }
    }
    for (int i=0; i<m1.rows; i++) {
        for (int j=0; j<m1.cols; j++) {
            for (int k=0; k<m2.cols; k++) {
                destination.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
}

// différence entre deux matrices
float diff_matrix(t_matrix m1, t_matrix m2) {
    float diff = 0;
    for (int i=0; i<m1.rows; i++) {
        for (int j=0; j<m1.cols; j++) {
            diff += fabs(m1.data[i][j] - m2.data[i][j]);    // fabs est une fonction mathématique, signifie "float absolute"
        }
    }
    return diff;
}

// afficher la matrice
void print_matrix(t_matrix matrix) {
    for (int i=0; i<matrix.rows; i++) {
        printf("|");
        for (int j=0; j<matrix.cols; j++) {
            printf("%d |", matrix.data[i][j]);
        }
        printf("|\n");
    }
}

// extraire une "sous-matrice"
t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index) {
    // 1. Récupérer la classe (composante) ciblée
    t_class currentClass = part.classes[compo_index];
    int size = currentClass.size;

    // 2. Créer la petite matrice carrée de la taille de la classe
    t_matrix sub = create_matrix(size, size);

    // 3. Remplir la sous-matrice
    // On parcourt les lignes (i) et colonnes (j) de la nouvelle petite matrice
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // On doit retrouver à quel numéro de sommet du graphe original cela correspond.
            // Attention : id_summit contient les ID (1, 2, 3...) mais la matrice utilise des indices (0, 1, 2...)
            // Il faut donc faire -1.
            int originalRow = currentClass.id_summit[i] - 1;
            int originalCol = currentClass.id_summit[j] - 1;

            // On copie la probabilité correspondante depuis la grande matrice
            sub.data[i][j] = matrix.data[originalRow][originalCol];
        }
    }
    return sub;
}