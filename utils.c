#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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

t_diagram createDiagram(const char *filename) {
    t_diagram diagram;

    diagram.layout = "elk";
    diagram.theme = "neo";
    diagram.look = "neo";
    diagram.adj_list = readGraph(filename);

    return diagram;
}

void writeDiagram(t_diagram diag, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Could not open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "---\nconfig:\n");
    fprintf(file, "layout: %s\ntheme: %s\nlook: %s\n---\n\n", diag.layout, diag.theme, diag.look);
    fprintf(file, "flowchart LR\n");
    char *id, *nextId;
    for (int i = 0; i < diag.adj_list.size; i++) {
        id = getID(i+1);
        fprintf(file, "%s((%d))\n", id, i+1);
    }
    fprintf(file, "\n");
    for (int i = 0; i < diag.adj_list.size; i++) {
        t_cell *cell = diag.adj_list.list[i].head;
        id = getID(i+1);
        while (cell) {
            nextId = getID(cell->summit);
            fprintf(file, "%s -->|%.2f|%s\n", id, cell->probability, nextId);
            cell = cell->next;
        }
    }
    fclose(file);
}