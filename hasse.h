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


















typedef struct lien{
	int start;
    int arive;
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
void initialiser_liens(liens *container);
void redimensionner_liens(liens *container);
int get_classe(int id_sommet, classify tableau_classif[], int nb_sommets_total);
int lien_existe(int c_dep, int c_arr, liens *container);
void ajouter_lien(int c_dep, int c_arr, liens *container);
void stck_le_lien(int n, struct classify *C);

int lien_existe(int c_dep, int c_arr, liens *container);
void ajouter_lien(int c_dep, int c_arr, liens *container);
#endif
