#ifndef __UTILS_H__
#define __UTILS_H__

typedef struct s_cell {
    int summit;
    float probability;
    struct s_cell *next;
} t_cell;

typedef struct s_list{
    t_cell *head;
} t_list;

typedef struct s_adjList {
    int size;
    t_list *list;
} t_adjList;

typedef struct s_diagram {
    char * layout;
    char * theme;
    char * look;
    t_adjList adj_list;
} t_diagram;

t_cell *create_cell(int summit, float probability);

t_list create_empty_list();

void add_cell(t_list *mylist, int summit , float probability);

void display_list(t_list *list);

t_adjList create_adj_list(int size);

void display_adj_list(t_adjList list);

t_adjList readGraph (const char *filename);

int is_markov_graph(t_adjList graph);

char *getID(int i);

t_diagram createDiagram(const char *filename);

void writeDiagram(t_diagram diagram, char * filename);

#endif