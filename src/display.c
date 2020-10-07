#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "defaults.h"
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
        // rouge
        printf("\033[0;31m");
        break;
    case PLAYER2:
        // bleu
        printf("\033[0;34m");
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
    printf("Bienvenue dans le jeu des 7 couleurs !\n");
    printf("**************************************\n\n");
}

void print_score(int score1, int score2)
{
    double p1 = (double)score1 / SCORE_MAX * 100;
    double p2 = (double)score2 / SCORE_MAX * 100;
    printf("Score : J1 ");
    set_print_color(PLAYER1);
    printf("%.0f%%", p1);
    reset_print_color();
    printf(" - J2 ");
    set_print_color(PLAYER2);
    printf("%.0f%%\n", p2);
    reset_print_color();
}

void print_turn(char player, int turn)
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
void print_board()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            char c = get_cell(i, j);
            set_print_color(c);
            printf(" %c", c);
            reset_print_color();
        }
        printf("\n");
    }
}

void print_end_screen(char winner, int score1, int score2)
{
    system("clear");
    print_score(score1, score2);
    print_board();
    if (winner == '0')
        printf("Égalité !\n");
    else
    {
        set_print_color(winner);
        printf("Le joueur %c remporte la partie !\n", winner);
        reset_print_color();
    }
}

void print_statistics(int nb_games, int wins1, int wins2, int total1, int total2)
{
    double avg1 = (double)total1 / (nb_games * SCORE_MAX) * 100;
    double avg2 = (double)total2 / (nb_games * SCORE_MAX) * 100;
    printf("\nRésultats du tournoi :\n");
    set_print_color(PLAYER1);
    printf("Joueur 1 : %d victoires - score moyen %.1f%%\n", wins1, avg1);
    set_print_color(PLAYER2);
    printf("Joueur 2 : %d victoires - score moyen %.1f%%\n", wins2, avg2);
    reset_print_color();
}
