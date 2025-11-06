#ifndef __UTILS_H__
#define __UTILS_H__

#include "list.h"

typedef struct s_diagram {
    char * layout;
    char * theme;
    char * look;
    int size;
    t_cell * cell;
} t_diagram;

static char *getID(int i);

t_diagram create_diagram(int size);

void write_diagram(t_diagram diagram);

#endif