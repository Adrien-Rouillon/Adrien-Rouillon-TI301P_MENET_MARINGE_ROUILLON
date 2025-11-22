#include <malloc.h>
#include "hasse.h"
#define TAILLE_INITIALE 10
/*
void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];
                            if ((link3.from == link2.to) && (link3.to == link1.to))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}

*/



// Initialise le conteneur de liens
void initialiser_liens(liens *container) {
    container->liens = (lien*)malloc(TAILLE_INITIALE * sizeof(lien));
    if (container->liens == NULL) {
        perror("Erreur d'allocation initiale");
        exit(EXIT_FAILURE);
    }
    container->nb_liens = 0;
    container->capacite = TAILLE_INITIALE;
}

// Redimensionne le tableau si la capacité est atteinte
void redimensionner_liens(liens *container) {
    container->capacite *= 2;
    container->liens = (lien*)realloc(container->liens, container->capacite * sizeof(lien));
    if (container->liens == NULL) {
        perror("Erreur de re-allocation");
        exit(EXIT_FAILURE);
    }
}

// Récupère la classe d'un sommet à partir du tableau de classification (Ci ou Cj)
int get_classe(int id_sommet, classify tableau_classif[], int nb_sommets_total) {
    for (int k = 0; k < nb_sommets_total; k++) {
        if (tableau_classif[k].sommet == id_sommet) {
            return tableau_classif[k].classe;
        }
    }
    return -1; // Sommet non trouvé
}

// Vérifie si le lien de classes (Ci, Cj) existe déjà dans le conteneur
int lien_existe(int c_dep, int c_arr, liens *container) {
    for (int k = 0; k < container->nb_liens; k++) {
        if (container->liens[k].start == c_dep && container->liens[k].arive == c_arr) {
            return 1; // Le lien existe
        }
    }
    return 0; // Le lien n'existe pas
}

// Ajoute le lien de classes au conteneur (avec vérification de la capacité)
void ajouter_lien(int c_dep, int c_arr, liens *container) {
    if (container->nb_liens >= container->capacite) {
        redimensionner_liens(container);
    }

    container->liens[container->nb_liens].start = c_dep;
    container->liens[container->nb_liens].arive = c_arr;
    container->nb_liens++;
}
