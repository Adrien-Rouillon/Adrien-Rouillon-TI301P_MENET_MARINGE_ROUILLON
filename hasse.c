#include <malloc.h>
#include "hasse.h"
#define TAILLE_INITIALE 10

void removeTransitiveLinks(liens *container)
{
    int i = 0;
    while (i < container->nb_liens)
    {
        lien link1 = container->liens[i];
        int j = 0;
        int to_remove = 0;
        while (j < container->nb_liens && !to_remove)
        {
            if (j != i)
            {
                lien link2 = container->liens[j];


                if (link1.start == link2.start)
                {

                    int k = 0;
                    while (k < container->nb_liens && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            lien link3 = container->liens[k];

                            if ((link3.start == link2.arive) && (link3.arive == link1.arive))
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
            // Remplacement par le dernier élément du tableau
            container->liens[i] = container->liens[container->nb_liens - 1];
            container->nb_liens--;
            // On n'incrémente pas i car on doit tester le lien qu'on vient de déplacer ici
        }
        else
        {
            i++;
        }
    }
}




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
