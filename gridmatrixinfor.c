/** @file   gridmatrixinfor.c
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  matrix information.
*/

#include "gridmatrixinfor.h"
#include <stdint.h>
#include <stdbool.h>



/** Initialize matrix grid.
@return matrix_grid*/
Grid* initialize_matrix_grid(void)
{
    uint8_t row_n = 0;
    uint8_t col_n = 0;
    static Grid matrix_grid[35];
    for (; row_n < 7;row_n++) {
        for (; col_n < 5;col_n++) {
            uint8_t index = row_n * 5 + col_n;
            matrix_grid[index].row = row_n;
            matrix_grid[index].column = col_n;
            matrix_grid[index].received = 0;
            matrix_grid[index].setted = 0;
            matrix_grid[index].navswitched = 0;
        }
    }

    return matrix_grid;
}
