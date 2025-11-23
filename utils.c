#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

//Créé une nouvelle cellule
t_cell *create_cell(int summit, float probability) {
    t_cell *cell = malloc(sizeof(t_cell));
    cell->summit = summit;
    cell->probability = probability;
    cell->next = NULL;
    return cell;
}

//Créé une liste vide
t_list create_empty_list() {
    t_list list;
    list.head = NULL;
    return list;
}

//Rajoute une nouvelle cellule dans la liste
void add_cell(t_list *list, int summit , float probability){
    t_cell * new = create_cell(summit,probability);
    new->next = list->head;
    list->head = new;
}

//Affiche la liste
void display_list(t_list *list) {
    t_cell *cell = list->head;
    printf("[head @] -> ");
    while (cell != NULL) {
        printf("(%d, %.2f)", cell->summit, cell->probability);
        if (cell->next != NULL) printf(" @-> ");
        cell = cell->next;
    }
}

//Créé une liste adjacente
t_adjList create_adj_list(int size) {
    t_adjList graph;
    graph.size = size;
    graph.list = malloc(sizeof(t_cell *) * size);
    for (int i = 0; i < size; i++) {
        graph.list[i] = create_empty_list();
    }
    return graph;
}

//Affiche une liste adjacente
void display_adj_list(t_adjList graph) {
    if (graph.size == 0) return;
    for (int i = 0; i < graph.size; i++) {
        printf("Liste pour le sommet %d: ", i+1);
        display_list(&graph.list[i]);
        printf("\n");
    }
}

//Lit un fichier donné et créé une liste adjacente à partir des données
t_adjList readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert, depart, arrivee;
    float proba;
    t_adjList graph;
    if (file==NULL){
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    if (fscanf(file, "%d", &nbvert) != 1){
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    graph = create_adj_list(nbvert);
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3){
        add_cell(&graph.list[depart-1], arrivee, proba);
    }
    fclose(file);
    return graph;
}

//Vérifie si le graphe est un graphe de Markov (Somme des proba sortante = 1).
int is_markov_graph(t_adjList graph) {
    int isMarkov = 1;
    //On vérifie pour chaque cellule.
    for (int i = 0; i < graph.size; i++) {
        float sum = 0;
        const t_cell *cell = graph.list[i].head;
        //On additionne chaque proba en sortie.
        while (cell) {
            sum += cell->probability;
            cell = cell->next;
        }
        //On regarde si somme est proche de 1.
        if (sum < 0.99 || sum > 1.00) {
            printf("La somme des probabilités du sommet %d est %f\n", i + 1, sum);
            isMarkov = 0;
        }
    }
    if (isMarkov) printf("Le graphe est un graphe de Markov\n");
    else printf("Le graphe n’est pas un graphe de Markov\n");
    return isMarkov;
}

char *getID(int i){
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    char *buffer = malloc(10 * sizeof(char));
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0){
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++) buffer[j] = temp[index - j - 1];
    buffer[index] = '\0';
    return buffer;
}

//crée un Diagramme
t_diagram createDiagram(const char *filename) {
    t_diagram diagram;

    diagram.layout = "elk";
    diagram.theme = "neo";
    diagram.look = "neo";
    diagram.adj_list = readGraph(filename);

    return diagram;
}

//vérifie s'il est vide et écrit le diagramme
void writeDiagram(t_diagram diag, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Could not open file for writing");
        exit(EXIT_FAILURE);
    }
    //Ecrit l'en tête du diagramme.
    fprintf(file, "---\nconfig:\n");
    fprintf(file, "layout: %s\ntheme: %s\nlook: %s\n---\n\n", diag.layout, diag.theme, diag.look);
    fprintf(file, "flowchart LR\n");
    char *id, *nextId;
    //Ecrit les noeuds du graphe.
    for (int i = 0; i < diag.adj_list.size; i++) {
        id = getID(i+1);
        fprintf(file, "%s((%d))\n", id, i+1);
    }
    fprintf(file, "\n");
    //Parcours-les liste d'adjacence.
    for (int i = 0; i < diag.adj_list.size; i++) {
        t_cell *cell = diag.adj_list.list[i].head;
        id = getID(i+1);
        while (cell) {// parcours-les sommet voisin
            nextId = getID(cell->summit);
            fprintf(file, "%s -->|%.2f|%s\n", id, cell->probability, nextId);
            cell = cell->next;
        }
        free(id);
    }
    fclose(file);
}