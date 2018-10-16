/** @file   checkwinner.c
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  check if win. Update win and continue flag.
*/
#include "checkwinner.h"
#include "gridmatrixinfor.h"

#include <stdint.h>
#include <stdbool.h>

/** Check if the player set or receive unbroken row of five leds horizontally.
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/

uint8_t check_horizontal(uint8_t row, Grid matrix_grid[], uint8_t receive_flag)
{
    uint8_t total_result = 0;
    uint8_t current_column;
    for (current_column = 0; current_column <= 4;current_column++) {

        uint8_t grid_i = row * 5 + current_column;

        if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag)
        {
            total_result++;
        } else {
             break;
        }
    }

    if (total_result == 4) {
            return 1;
    } else {
            return 0;
    }
}


/** Check if the player set or receive unbroken row of five leds vertically.
    @param column
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/
uint8_t check_vertical(uint8_t column, uint8_t row,Grid matrix_grid[],uint8_t receive_flag)
{
    uint8_t total_result = 0;
    int8_t current_row;

    total_result++;

    for(current_row = row - 1; current_row >= 0; current_row--) {
        if (total_result == 4) {
            break;
        } else {

            uint8_t grid_i = current_row * 5 + column;
            if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
                total_result++;
            } else {
                break;
            }
        }

    }

    for(current_row = row + 1; current_row <= 6; current_row++) {
        if (total_result == 4) {
            break;
        } else {

            uint8_t grid_i = current_row * 5 + column;
            if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
                total_result++;
            } else {
                break;
            }
        }

    }

    if (total_result == 4) {
        return 1;
    } else {
        return 0;
    }
}

/** Check if the player set or receive unbroken row of five leds diagonally.
    @param column
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/

uint8_t check_cross_backslash(uint8_t column, uint8_t row,Grid matrix_grid[], uint8_t receive_flag)
{
    uint8_t total_result = 0;
    total_result++;

    int8_t current_column = column - 1;
    int8_t current_row = row + 1;

    while (current_column != -1) {
        uint8_t grid_i = current_row * 5 + current_column;
        if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
            total_result++;
            current_row++;
            current_column--;
        } else {
            break;
        }
    }

    current_column = column + 1;
    current_row = row - 1;

    while (current_column != 5) {
        uint8_t grid_i = current_row * 5 + current_column;
        if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
            total_result++;
            current_row--;
            current_column++;
        } else {
            break;
        }
    }

    if (total_result == 4) {
        return 1;
    } else {
        return 0;
    }

}

/** Check if the player set or receive unbroken row of five leds diagonally.
    @param column
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/

uint8_t check_cross_slash(uint8_t column, uint8_t row,Grid matrix_grid[], uint8_t receive_flag)
{
    uint8_t total_result = 0;
    total_result++;

    int8_t current_column = column + 1;
    int8_t current_row = row + 1;

    while (current_column != 5) {
        uint8_t grid_i = current_row * 5 + current_column;
        if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
            total_result++;
            current_row++;
            current_column++;
        } else {
            break;
        }
    }

    current_column = column - 1;
    current_row = row - 1;

    while (current_column != 5) {
        uint8_t grid_i = current_row * 5 + current_column;
        if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == receive_flag) {
            total_result++;
            current_row--;
            current_column--;
        } else {
            break;
        }
    }

    if (total_result == 4) {
        return 1;
    } else {
        return 0;
    }

}


/** Check if the player set or receive unbroken row of five leds diagonally.
    @param matrix
    @return non-zero for success*/
uint8_t over_Done(Grid matrix_grid[])
{
    uint8_t total_setted = 0;
    while(total_setted <= 34) {
        if (matrix_grid[total_setted].setted == 1) {
            total_setted++;
            continue;
        } else {
            break;
        }
    }

    if (total_setted == 35) {
        return 1;
    } else {
        return 0;
    }
}

