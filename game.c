/** @file   game.c
    @author Min Zhang & Bill Liu
    @date   8 Oct 2018
    @brief  Main game
*/



#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "checkwinner.h"
#include "gridmatrixinfor.h"
#include "preCharandIndex.h"
#include "pio.h"

#include <avr/io.h>

#include <stdio.h>

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define GRID_NUMBER 35

#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)
#define TUNZ_F 440
#define LOOP_RATE (TUNZ_F * 2)

/* This needs to be fast enough to prevent the eye noticing flicker.
   A lower value (say 5) is useful for flashing pixels.  */
#define LUMINANCE_STEP 10


static uint8_t sequence = 1;
static uint8_t pwm_tick = 0;


static Grid matrix_grid[35] = {
    {.column = 0, .row = 0, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 0, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 0, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 0, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 0, .setted = 0, .received = 0, .navswitched = 0},


    {.column = 0, .row = 1, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 1, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 1, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 1, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 1, .setted = 0, .received = 0, .navswitched = 0},

    {.column = 0, .row = 2, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 2, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 2, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 2, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 2, .setted = 0, .received = 0, .navswitched = 0},


    {.column = 0, .row = 3, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 3, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 3, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 3, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 3, .setted = 0, .received = 0, .navswitched = 0},


    {.column = 0, .row = 4, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 4, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 4, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 4, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 4, .setted = 0, .received = 0, .navswitched = 0},

    {.column = 0, .row = 5, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 5, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 5, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 5, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 5, .setted = 0, .received = 0, .navswitched = 0},



    {.column = 0, .row = 6, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 1, .row = 6, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 2, .row = 6, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 3, .row = 6, .setted = 0, .received = 0, .navswitched = 0},
    {.column = 4, .row = 6, .setted = 0, .received = 0, .navswitched = 0}

};

/** display character on the matrex
    @param character
*/
void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/** display the led for both player.
 * LED displayed by one player shows static on one's own board but flashing on another's board
*/

void display_matrix(void)
{
    uint8_t col;
    uint8_t row;

    for (col = 0; col < TINYGL_WIDTH; col++) {
        for (row = 0; row < TINYGL_HEIGHT; row++) {
            uint8_t grid_i = row * 5 + col;
            if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == 0) {
                /*Player set the led*/
                tinygl_draw_point (tinygl_point(col, row), 1);
            } else if (matrix_grid[grid_i].setted == 1 && matrix_grid[grid_i].received == 1) {
                /*Player received the led, flash the led*/
                tinygl_draw_point (tinygl_point(col, row), LUMINANCE_STEP > pwm_tick - 8);
            } else {
                if (matrix_grid[grid_i].navswitched == 0) {
                    tinygl_draw_point (tinygl_point(col, row), 0);
                } else {
                    tinygl_draw_point (tinygl_point(col, row), 1);;
                }


            }
        }
    }

    pwm_tick++;

    if (pwm_tick >= 100) {
        pwm_tick = 0;
    }
}

int main (void)
{


    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);

    pio_config_set (PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set (PIEZO2_PIO, PIO_OUTPUT_HIGH);



    uint8_t current_row = 0;
    uint8_t current_column = 0;
    uint8_t continue_flag = 1;
    uint8_t win_flag = 0;


    char character;

    DDRC |= (1<<2);



    while (1) {

        pacer_wait ();
        tinygl_update ();
        navswitch_update ();




        if (continue_flag) {
            //Game is not over,display the grid

            display_matrix();

            /*Find current row and col which can be setted*/

            tinygl_draw_point(tinygl_point(current_column,current_row),1);

            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                tinygl_draw_point(tinygl_point(current_column,current_row),0);


                if (current_row == 6) {
                    current_row = 0;
                } else {
                    current_row++;
                }
                uint8_t grid_i = current_row * 5 + current_column;
                if (matrix_grid[grid_i].setted == 0) {
                    tinygl_draw_point(tinygl_point(current_column,current_row),1);
                } else {
                    /*give some sounds*/
                }

            }

            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {


                tinygl_draw_point(tinygl_point(current_column,current_row),0);
                if (current_row == 0) {
                    current_row = 6;
                } else {

                    current_row--;
                }

                uint8_t grid_i = current_row * 5 + current_column;
                if (matrix_grid[grid_i].setted == 0) {
                    tinygl_draw_point(tinygl_point(current_column,current_row),1);
                } else {
                    /*give some sounds*/;
                }

            }

            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                tinygl_draw_point(tinygl_point(current_column,current_row),0);
                if (current_column == 0) {
                    current_column = 4;
                } else {
                    current_column--;
                }

                uint8_t grid_i =  current_row * 5 + current_column;;
                if (matrix_grid[grid_i].setted == 0) {
                    tinygl_draw_point(tinygl_point(current_column,current_row),1);
                } else {
                    /*give some sounds*/;
                }
            }

            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                tinygl_draw_point(tinygl_point(current_column,current_row),0);
                if (current_column == 4) {
                    current_column = 0;
                } else {
                    current_column++;
                }

                uint8_t grid_i = current_row * 5 + current_column;;
                if (matrix_grid[grid_i].setted == 0) {
                    tinygl_draw_point(tinygl_point(current_column,current_row),1);
                } else {
                    /*give some sounds*/;
                }
            }

            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {

                pio_output_toggle(PIEZO1_PIO);
                pio_output_toggle(PIEZO2_PIO);

                uint8_t grid_i = current_row * 5 + current_column;
                /** Get character which will be send to another player.
                    @param index
                    @return character*/
                character = get_character(grid_i);

                if (matrix_grid[grid_i].setted == 0) {

                    /*If the player's sequence is 1,player can set the led.Otherwise, the led can not be setted.*/

                    if (sequence) {
                        matrix_grid[grid_i].setted = 1; /*Set led*/
                        sequence = 0; /*Before player recevied led, the player can not set led again.*/

                        /* Write character to IR_UART.  This blocks until the character is
                            written.  It then checks if data has been received and if so, reads
                            the data and throws it away on the assumption that it is electrical or optical echoing.  */

                        ir_uart_putc(character);

                        /*Check if get unbroken row of five leds horizontally,vertically,or diagonally,or overrun.
                         * If 1: game over.Update continue flag to 0. If not overrun, win flag equal to 1.*/

                        if (check_horizontal(current_row,matrix_grid,0)||check_vertical(current_column,current_row,matrix_grid,0) || check_cross_backslash(current_column,current_row,matrix_grid,0) || check_cross_slash(current_column,current_row,matrix_grid,0)) {
                            continue_flag = 0;
                            win_flag = 1;
                            PORTC |= (1<<2);
                        } else {
                            if (over_Done(matrix_grid)) {
                                continue_flag = 0;
                                win_flag = 2;
                            }
                        }

                    }
                }
            }

            /* Return non-zero if there is a character ready to be read.  */

            if (ir_uart_read_ready_p()) {
                /* Read character from IR_UART.  This blocks if nothing
                   is available to read.  */
                character = ir_uart_getc();

                /** Get index as the received character.
                    @param character
                    @return index*/

                uint8_t grid_index = get_index(character);

                if (matrix_grid[grid_index].setted == 0) {
                    /*Set led*/
                    matrix_grid[grid_index].setted = 1;
                    matrix_grid[grid_index].received = 1;

                    sequence = 1; /*Player recevied led, the player can  set led again.*/

                    if (check_horizontal(matrix_grid[grid_index].row,matrix_grid,1) || check_vertical(matrix_grid[grid_index].column, matrix_grid[grid_index].row,matrix_grid,1) || check_cross_slash(matrix_grid[grid_index].column, matrix_grid[grid_index].row,matrix_grid,1) || check_cross_backslash(matrix_grid[grid_index].column, matrix_grid[grid_index].row,matrix_grid,1)) {

                        /*Check if get unbroken row of five leds horizontally,vertically,or diagonally,or overrun.
                         * If 1: game over.Update continue flag to 0. Else,check overrun.*/
                        continue_flag = 0;


                    } else if (over_Done(matrix_grid)) {
                        continue_flag = 0;
                        win_flag = 2;
                    }
                }
            }

        } else {
            if (win_flag == 1) {
                display_character('W');
            } else if (win_flag == 0) {
                display_character('F');
            } else if (win_flag == 2) {
                display_character('T');
            }
        }
    }

    return 0;
}


