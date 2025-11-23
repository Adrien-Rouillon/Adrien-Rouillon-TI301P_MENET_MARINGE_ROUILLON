#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "hasse.h"
#include "tarjan.h"
#include "utils.h"
#define TAILLE_INITIALE 10

//Supprime les liens transitifs du diagramme de Hasse
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
                    // look for a link from link2.to to link1.to
                    int k = 0;

                    while (k < container->nb_liens && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            // remove link1 by replacing it with the last link
                            lien link3 = container->liens[k];
                            if ((link3.start == link2.arrive) && (link3.arrive == link1.arrive))
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

            container->liens[i] = container->liens[container->nb_liens - 1];
            container->nb_liens--;
        }
        else
        {
            i++;
        }
    }
}
//Initialise le conteneur de liens avec une capacité initiale
void initialize_link(liens *container) {
    // Allocation dynamique du tableau de liens
    container->liens = (lien*)malloc(TAILLE_INITIALE * sizeof(lien));
    if (container->liens == NULL) {
        perror("Erreur d'allocation initiale");
        exit(EXIT_FAILURE);
    }
    container->nb_liens = 0;
    container->capacite = TAILLE_INITIALE;
}

//Double la capacité du conteneur lorsqu'il est plein
void resize_link(liens *container) {
    container->capacite *= 2;

    // Réallouer le tableau avec la nouvelle taille
    container->liens = (lien*)realloc(container->liens, container->capacite * sizeof(lien));
    if (container->liens == NULL) {
        perror("Erreur de re-allocation");
        exit(EXIT_FAILURE);
    }
}
//Trouve l'index de la classe contenant un sommet donné
int find_class_vertex(t_partition part, int summit_id) {
    // Parcourt toutes les classes de la partition
    for (int i = 0; i < part.size; i++) {
        for (int j = 0; j < part.classes[i].size; j++) {
            if (part.classes[i].id_summit[j] == summit_id) {
                return i;
            }
        }
    }
    return -1;
}
//Vérifie si un lien entre deux classes existe déjà dans le conteneur
int existing_link(int c_dep, int c_arr, liens *container) {
    // Parcourt tous les liens existants
    for (int k = 0; k < container->nb_liens; k++) {
        if (container->liens[k].start == c_dep && container->liens[k].arrive == c_arr) {
            return 1;
        }
    }
    return 0; // Le lien n'existe pas encore
}
//Ajoute un nouveau lien entre deux classes dans le conteneur
void add_link(int c_dep, int c_arr, liens *container) {

    if (container->nb_liens >= container->capacite) {
        resize_link(container);
    }

    // Ajouter le nouveau lien à la fin du tableau
    container->liens[container->nb_liens].start = c_dep;
    container->liens[container->nb_liens].arrive = c_arr;
    container->nb_liens++;
}
//Crée le diagramme de Hasse à partir du graphe et de sa partition
liens create_diagram_hasse(t_adjList graph, t_partition part) {
    liens container;
    initialize_link(&container); // Initialiser le conteneur de liens

    // Parcourir tous les sommets du graphe original
    for (int i = 0; i < graph.size; i++) {

        int classe_depart = find_class_vertex(part, i + 1);

        if (classe_depart == -1) continue;

        // Parcourir tous les successeurs de ce sommet dans le graphe
        t_cell *cell = graph.list[i].head;
        while (cell) {

            int classe_arrivee = find_class_vertex(part, cell->summit + 1);

            if (classe_arrivee == -1) {
                cell = cell->next;
                continue;
            }

            // Si les deux sommets sont dans des classes DIFFÉRENTES
            if (classe_depart != classe_arrivee) {

                if (!existing_link(classe_depart, classe_arrivee, &container)) {
                    add_link(classe_depart, classe_arrivee, &container);
                }
            }

            cell = cell->next;
        }
    }
    removeTransitiveLinks(&container);
    return container;
}

//Affiche le diagramme de Hasse de manière lisible
void print_diagramme_hasse(liens container, t_partition part) {
    printf("Diagramme de Hasse\n");
    printf("Nombre de liens entre classes : %d\n", container.nb_liens);

    // Afficher les classes avec leurs sommets
    printf("Classes :\n");
    for (int i = 0; i < part.size; i++) {
        printf("%s : {", part.classes[i].name);
        for (int j = 0; j < part.classes[i].size; j++) {
            printf("%d", part.classes[i].id_summit[j]);
            if (j < part.classes[i].size - 1) {
                printf(", ");
            }
        }
        printf("}\n");
    }

    // Afficher les liens entre classes
    printf("\nLiens entre classes :\n");
    for (int i = 0; i < container.nb_liens; i++) {
        printf("%s -> %s\n",
               part.classes[container.liens[i].start].name,
               part.classes[container.liens[i].arrive].name);
    }
}
void free_link(liens *container) {
    free(container->liens);
    container->liens = NULL;
    container->nb_liens = 0;
    container->capacite = 0;
}
void characteristic(liens container,t_partition part){
  int *has_outgoing_link = (int*)calloc(part.size, sizeof(int));
  for (int i = 0; i < container.nb_liens; i++) {
        int classe_depart_id = container.liens[i].start;
        int classe_arrivee_id = container.liens[i].arrive;

        if (classe_depart_id != classe_arrivee_id) {
             has_outgoing_link[classe_depart_id] = 1;
        }
  }
  for(int i = 0; i< part.size;i++){
    printf("classe %s : {",part.classes[i].name);
    for (int j = 0; j < part.classes[i].size; j++) {
    	printf("%d%s", part.classes[i].id_summit[j],(j< part.classes[i].size-1)? ", " : "");
	}
  	printf("}");
  	if (has_outgoing_link[i] == 1) {
    		printf("**TRANSIOIRE**\n");
  	} else {
  		printf("**PERSISTANTE**\n");
  	}
 	if ( part.classes[i].size == 1){
  		printf("%d est **Absorbant**\n",part.classes[i].id_summit[0]);
  	}

  }
  if(part.size ==1){
    printf("Le graphe est **IREDUCTIBLE**");
  }else{
  	printf("Le graphe n'est pas **IREEDUCTIBLE**");
  }
  printf("}\n");
  free(has_outgoing_link);
}

