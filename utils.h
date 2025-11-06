#ifndef __UTILS_H__
#define __UTILS_H__

#include "list.h"

typedef struct s_diagram {
    char * layout;
    char * theme;
    char * look;
    t_adjacent_list adj_list;
} t_diagram;

char *getID(int i);

t_diagram createDiagram(const char *filename);

void writeDiagram(t_diagram diagram, char * filename);

#endif