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

#endif