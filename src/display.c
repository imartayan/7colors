#include "display.h"

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
    printf("Welcome to the 7 wonders of the world of the 7 colors\n");
    printf("*****************************************************\n\n");
}

void print_score(int score1, int score2)
{
    double p1 = (double)score1 / SCORE_MAX * 100;
    double p2 = (double)score2 / SCORE_MAX * 100;
    printf("\nScore : J1 ");
    set_print_color(PLAYER1);
    printf("%.0f%%", p1);
    reset_print_color();
    printf(" - J2 ");
    set_print_color(PLAYER2);
    printf("%.0f%%\n", p2);
    reset_print_color();
}

void print_turn(char curr_player, int turn)
{
    printf("Tour %d - ", turn);
    printf("C'est à ");
    set_print_color(curr_player);
    printf("J%c", curr_player);
    reset_print_color();
    printf(" de jouer !\n");
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(char* board)
{
    // printf("Etat actuel du plateau :\n");
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            char c = get_cell(board, i, j);
            set_print_color(c);
            printf("%c ", c);
            reset_print_color();
        }
        printf("\n");
    }
}

void print_end_screen(char* board, char winner, int mode, int score1, int score2)
{
    system("clear");
    print_score(score1, score2);
    print_board(board);
    if (winner == '0')
        printf("Egalite !\n");
    else if (mode == 1)
        printf("Le joueur %c remporte la partie !\n", winner);
    else
    {
        if (winner == PLAYER1)
            printf("Vous remportez la partie !\n");
        else
            printf("L'ordinateur remporte la partie !\n");
    }
}
