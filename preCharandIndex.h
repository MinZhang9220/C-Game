/** @file   preCharandIndex.h
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  Get character to send and get index as given the received character.
*/

#ifndef PRECHARANDINDEX_H
#define PRECHARANDINDEX_H

#include <stdint.h>
#include <stdbool.h>


/** Get character which will be send to another player.
@param index
@return character*/



char get_character(uint8_t index);

/** Get index as the received character.
@param character
@return index*/


uint8_t get_index(char chara);


#endif

