#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "board.h"

// Properly printing colors
void reset_print_color()
{
    printf("\033[0m");
}

void set_print_color(char c)
{
    switch (c)
    {
    case 'R':
        //rouge
        printf("\033[0;31m");
        break;

    case 'V':
        //vert
        printf("\033[0;32m");
        break;

    case 'B':
        //bleu
        printf("\033[0;34m");
        break;

    case 'J':
        //jaune
        printf("\033[0;33m");
        break;

    case 'G':
        // gris/blanc (couleur de départ)
        break;

    case 'M':
        // magenta
        printf("\033[0;35m");
        break;

    case 'C':
        // cyan
        printf("\033[0;36m");
        break;

    default:
        reset_print_color();
    }
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(char curr_player, int tour, int score1, int score2)
{
    system("clear");
    printf("Tour %d - Score J1: %d - Score J2: %d\n", tour, score1, score2);
    printf("C'est au tour du joueur %c\n", curr_player);
    printf("Etat actuel du plateau :\n");
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            char c = get_cell(i, j);
            if (c == PLAYER1 || c == PLAYER2)
                printf("%c ", c);
            else
            {
                set_print_color(c);
                printf("%c ", 219);
                reset_print_color();
            }
        }
        printf("\n");
    }
}

void print_end_screen(int winner)
{
    printf("Le joueur %d remporte la partie !", winner);
}
