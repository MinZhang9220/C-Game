/** @file   gridmatrixinfor.h
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  matrix information.
*/

#ifndef GRIDMATRIXINFOR_H
#define GRIDMATRIXINFOR_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_GRID 35

/* Led matrix configuration structure.  */
typedef struct grid_s
{
    uint8_t column;
    uint8_t row;
    bool setted;
    bool received;
    bool navswitched;
} Grid;

/** Initialize matrix grid.
@return matrix_grid*/

Grid* initialize_matrix_grid(void);


#endif
