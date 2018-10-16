/** @file   checkwinner.h
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  check if win. Update win and continue flag.
*/

#ifndef CHECKWINNER_H
#define CHECKWINNER_H

#include "gridmatrixinfor.h"
#include <stdint.h>
#include <stdbool.h>

/** Check if the player set or receive unbroken row of five leds horizontally.
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/



uint8_t check_horizontal(uint8_t row, Grid matrix[], uint8_t receive_flag);

/** Check if the player set or receive unbroken row of five leds vertically.
    @param column
    @param row
    @param matrix



    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/


uint8_t check_vertical(uint8_t column, uint8_t row,Grid matrix[],uint8_t receive_flag);

/** Check if the player set or receive unbroken row of five leds diagonally.
    @param column
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/


uint8_t check_cross_backslash(uint8_t column, uint8_t row,Grid matrix[], uint8_t receive_flag);

/** Check if the player set or receive unbroken row of five leds diagonally.
    @param column
    @param row
    @param matrix
    @param receove_flag. If 1, check receive. If 0, check set.
    @return non-zero for success*/


uint8_t check_cross_slash(uint8_t column, uint8_t row,Grid matrix[], uint8_t receive_flag);

/** Check if the player set or receive unbroken row of five leds diagonally.
    @param matrix
    @return non-zero for success*/

uint8_t over_Done(Grid matrix[]);


#endif
