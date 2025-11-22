#include "tarjan.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


//Convertie une liste adjacente en une liste Tarjan Vertex, plus utile pour cette partie.
t_tarjanVtx *listAdj_to_TarjanVtx(t_adjList graph) {
    if (graph.size <= 0) perror("ERROR: listAdj_to_Tarjan");
    t_tarjanVtx * list = malloc(sizeof(t_tarjanVtx)*graph.size);
    for (int i = 0; i < graph.size; i++) {
        list[i].id = i+1;
        list[i].temp_num = -1;
        list[i].access_num = -1;
        list[i].index = 0;
    }
    return list;
}

//Rajoute à la pile l'ID du sommet donné.
void stack_pile(t_pile *pile, int val) {
    pile->elements[pile->size] = val;
    pile->size++;
}

//Fonction de parcours du graphe pour chercher à former une classe.
void tarjan_parkour(t_adjList graph, t_tarjanVtx *list, t_pile *pile, t_partition *part, int *count, int index) {
    //Initialisation du premier sommet donné avec les données.
    t_tarjanVtx *curSummit = &list[index];
    curSummit->temp_num = *count;
    curSummit->access_num = *count;
    (*count)++;
    stack_pile(pile, curSummit->id);
    curSummit->index = 1;
    //On utilise la liste adjacente, car on peut suivre les connexions entre sommets.
    t_cell *cell = graph.list[index].head;
    //Parcours de tous les successeurs du sommet.
    while (cell) {
        //Si le sommet n'a pas encore été visité, appel récursif de Tarjan.
        if (list[cell->summit].temp_num == -1) {
            tarjan_parkour(graph, list, pile, part, count, cell->summit);
        //Sinon, on vérifie s'il est dans la pile.
        } else if (list[cell->summit].index == 1) {
            //Si le sommet actuel a un num d'accès plus grand que son prochain, on égalise les 2 num.
            //Cela signifie que tous les sommets entre les deux font partie d'une classe.
            if (list[cell->summit].access_num < curSummit->access_num) {
                curSummit->access_num = list[cell->summit].access_num;
            }
        }
        cell = cell->next;
    }
    //Si le sommet a le même num d'accès que son ordre de découverte,
    //cela veut dire qu'on peut créer une nouvelle classe.
    if (curSummit->temp_num == curSummit->access_num) {
        t_class newClass;
        newClass.size = 0;
        newClass.id_summit = malloc(sizeof(int) * graph.size);
        int idSummitUnpile;
        //Tant qu'on n'est pas au fond de la pile, on dépile et on rajoute dans la classe.
        do {
            idSummitUnpile = pile->elements[pile->size - 1];
            pile->size--;
            t_tarjanVtx *summitUnpile = &list[idSummitUnpile - 1];
            summitUnpile->index = 2;
            newClass.id_summit[newClass.size++] = idSummitUnpile;
        } while (idSummitUnpile != curSummit->id);
        snprintf(newClass.name,sizeof(newClass.name),"C%d",part->size);
        //On rajoute la classe dans la partition du graphe.
        part->classes[part->size] = newClass;
        part->size++;
    }
}

//Fonction qui initialise les valeurs et qui tourne le parcours de Tarjan.
t_partition tarjan(t_adjList graph) {
    //Initialise les variables nécéssaires.
    t_partition part;
    part.classes = malloc(sizeof(t_class) * graph.size);
    part.size = 0;
    t_tarjanVtx *list = listAdj_to_TarjanVtx(graph);
    t_pile pile;
    pile.elements = malloc(sizeof(int) * graph.size);
    pile.size = 0;
    int count = 0;
    //Pour chaque sommet, on vérifie s'il est deja ou pas dans une classe,
    //et lance tarjan_parcours pour former une nouvelle classe.
    for (int i = 0; i < graph.size; i++) {
        if (list[i].temp_num == -1) {
            tarjan_parkour(graph, list, &pile, &part, &count, i);
        }
    }
    free(list);
    free(pile.elements);
    return part;
}

//Fonction pour afficher la partition du graphe
void print_partition(t_partition part) {
    for (int i = 0; i < part.size; i++) {
        printf("Composante %s: {", part.classes[i].name);
        for (int j = 0; j < part.classes[i].size; j++) {
            printf("%d", part.classes[i].id_summit[j]);
            if (j < part.classes[i].size - 1) {
                printf(",");
            }
        }
        printf("}\n");
    }
}