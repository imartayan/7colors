/*******************************************************
Role ........ : définition des fonctions qui font l'affichage du jeu
Auteurs ...... : Clément MORAND, Igor Martayan
dernière modification : 12/10/2020
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "utils.h"

// Properly printing colors
void reset_print_color()
{
    printf("\033[0m");
}

void set_print_color(char c)
{
    switch (c)
    {
    case PLAYER1:
        // cyan
        printf("\033[0;36m");
        break;
    case PLAYER2:
        // jaune
        printf("\033[0;33m");
        break;
    case 'R':
        // rouge
        printf("\033[1;31m");
        break;
    case 'V':
        // vert
        printf("\033[1;32m");
        break;
    case 'B':
        // bleu
        printf("\033[1;34m");
        break;
    case 'J':
        // jaune
        printf("\033[1;33m");
        break;
    case 'G':
        // gris/blanc (couleur de départ)
        printf("\033[1m");
        break;
    case 'M':
        // magenta
        printf("\033[1;35m");
        break;
    case 'C':
        // cyan
        printf("\033[1;36m");
        break;
    default:
        reset_print_color();
    }
}

void print_welcome_screen()
{
    system("clear");
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 83, 97, 108, 117, 116, 32, 97, 32, 116, 111, 105, 44, 32, 106, 101, 117, 110, 101, 32, 101, 110, 116, 114, 101, 112, 114, 101, 110, 101, 117, 114, 32, 33, 10);
    printf("Bienvenue dans le jeu des 7 couleurs !\n");
    printf("**************************************\n\n");
}

void print_score(State *state)
{
    int score_max = state->board_size * state->board_size;
    double p1 = (double)state->player1->score / score_max * 100;
    double p2 = (double)state->player2->score / score_max * 100;
    printf("Score : J1 ");
    set_print_color(state->player1->id);
    printf("%.2f%%", p1);
    reset_print_color();
    printf(" - J2 ");
    set_print_color(state->player2->id);
    printf("%.2f%%\n", p2);
    reset_print_color();
}

void print_turn(int turn, char player)
{
    printf("Tour %d - ", turn);
    printf("C'est à ");
    set_print_color(player);
    printf("J%c", player);
    reset_print_color();
    printf(" de jouer !\n");
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(char *board, int board_size)
{
    int x, y;
    for (y = board_size - 1; y >= 0; y--)
    {
        for (x = 0; x < board_size; x++)
        {
            char c = get_cell(board, board_size, x, y);
            set_print_color(c);
            printf(" %c", c);
            reset_print_color();
        }
        printf("\n");
    }
}

void print_end_screen(char winner, State *state)
{
    system("clear");
    print_score(state);
    print_board(state->board, state->board_size);
    if (winner == '0')
        printf("Égalité !\n");
    else
    {
        set_print_color(winner);
        printf("Le joueur %c remporte la partie !\n", winner);
        reset_print_color();
    }
}

void print_statistics(State *state, int nb_games, int wins1, int wins2, int total1, int total2)
{
    int score_max = state->board_size * state->board_size;
    double avg1 = (double)total1 / (nb_games * score_max) * 100;
    double avg2 = (double)total2 / (nb_games * score_max) * 100;
    printf("\nRésultats du tournoi :\n");
    set_print_color(state->player1->id);
    printf("Joueur 1 : %d victoires - score moyen %.2f%%\n", wins1, avg1);
    set_print_color(state->player2->id);
    printf("Joueur 2 : %d victoires - score moyen %.2f%%\n", wins2, avg2);
    reset_print_color();
}
