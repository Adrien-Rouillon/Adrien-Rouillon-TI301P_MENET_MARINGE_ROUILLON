//
// Created by Adrien on 22/10/2025.
//

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

t_cell create_cell(int summit, int probability) {
    t_cell cell;
    cell.summit = summit;
    cell.probability = probability;
    cell.next = NULL;
}

