/** @file   preCharandIndex.h
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  Get character to send and get index as given the received character.
*/


#include "preCharandIndex.h"
#include <stdint.h>
#include <stdbool.h>

/** Get character which will be send to another player.
    @param index
    @return character*/

char get_character(uint8_t grid_i)
{

    char character;


    switch (grid_i) {
        case 0:
        character = '0';
        break;
        case 1:
        character = '1';
        break;
        case 2:
        character = '2';
        break;
        case 3:
        character = '3';
        break;
        case 4:
        character = '4';
        break;
        case 5:
        character = '5';
        break;
        case 6:
        character = '6';
        break;
        case 7:
        character = '7';
        break;
        case 8:
        character = '8';
        break;
        case 9:
        character = '9';
        break;
        case 11:
        character = 'A';
        break;
        case 12:
        character = 'B';
        break;
        case 13:
        character = 'C';
        break;
        case 14:
        character = 'D';
        break;
        case 15:
        character = 'E';
        break;
        case 16:
        character = 'F';
        break;
        case 17:
        character = 'G';
        break;
        case 18:
        character = 'H';
        break;
        case 19:
        character = 'I';
        break;
        case 20:
        character = 'J';
        break;
        case 21:
        character = 'K';
        break;
        case 22:
        character = 'L';
        break;
        case 23:
        character = 'M';
        break;
        case 24:
        character = 'N';
        break;
        case 25:
        character = 'O';
        break;
        case 26:
        character = 'P';
        break;
        case 27:
        character = 'Q';
        break;
        case 28:
        character = 'R';
        break;
        case 29:
        character = 'S';
        break;
        case 30:
        character = 'T';
        break;
        case 31:
        character = 'U';
        break;
        case 32:
        character = 'V';
        break;
        case 33:
        character = 'W';
        break;
        case 34:
        character = 'X';
        break;
        case 10:
        character = 'Y';
        break;
    }

    return character;
}

/** Get index as the received character.
@param character
@return index*/


uint8_t get_index(char chara)
{
    uint8_t grid_index;
    switch (chara) {
        case '0':
        grid_index = 0;
        break;
        case '1':
        grid_index = 1;
        break;
        case '2':
        grid_index = 2;
        break;
        case '3':
        grid_index = 3;
        break;
        case '4':
        grid_index = 4;
        break;
        case '5':
        grid_index = 5;
        break;
        case '6':
        grid_index = 6;
        break;
        case '7':
        grid_index = 7;
        break;
        case '8':
        grid_index = 8;
        break;
        case '9':
        grid_index = 9;
        break;
        case 'Y':
        grid_index = 10;
        break;
        case 'A':
        grid_index = 11;
        break;
        case 'B':
        grid_index = 12;
        break;
        case 'C':
        grid_index = 13;
        break;
        case 'D':
        grid_index = 14;
        break;
        case 'E':
        grid_index = 15;
        break;
        case 'F':
        grid_index = 16;
        break;
        case 'G':
        grid_index = 17;
        break;
        case 'H':
        grid_index = 18;
        break;
        case 'I':
        grid_index = 19;
        break;
        case 'J':
        grid_index = 20;
        break;
        case 'K':
        grid_index = 21;
        break;
        case 'L':
        grid_index = 22;
        break;
        case 'M':
        grid_index = 23;
        break;
        case 'N':
        grid_index = 24;
        break;
        case 'O':
        grid_index = 25;
        break;
        case 'P':
        grid_index = 26;
        break;
        case 'Q':
        grid_index = 27;
        break;
        case 'R':
        grid_index = 28;
        break;
        case 'S':
        grid_index = 29;
        break;
        case 'T':
        grid_index = 30;
        break;
        case 'U':
        grid_index = 31;
        break;
        case 'V':
        grid_index = 32;
        break;
        case 'W':
        grid_index = 33;
        break;
        case 'X':
        grid_index = 34;
        break;
    }

    return grid_index;

}
