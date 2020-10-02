/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Implentation of the board module */

#include <stdio.h> /* Import printf */
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "board.h"            /* Enforce that the header file matches the declarations */
#include "simple_unit_test.h" /* Import the testing infrastructure */

/* Note: This template comes with several global definitions. For now.
 *
 * Such globals are usually discouraged, but having a few of them is OK in a C program.
 * At first, no dinosaure will get you if you use globals, but you should seek for a better
 * solution for your final version.
 *
 * Encapuslating them in an appropriate data structure, and removing all globals would be a must.
 * Plus, this path often leads to simpler code, that is easier to test.
 */

/** Represent the actual current board game */
char board[BOARD_SIZE * BOARD_SIZE] = {0}; // Filled with zeros

const char player1 = '1', player2 = '2';
const point start1 = {BOARD_SIZE - 1, 0}, start2 = {0, BOARD_SIZE - 1};
const int score1 = 0, score2 = 0;

const char colors[] = {'R', 'V', 'B', 'J', 'G', 'M', 'C'};
point direction[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

/** Retrieves the color of a given board cell */
char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

// init the board with random colors
void init_board()
{
    int n;
    char color;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            n = rand() % NB_COLORS;
            color = colors[n];
            set_cell(i, j, color);
        }
    }
    set_cell(start1.x, start1.y, player1);
    set_cell(start2.x, start2.y, player2);
}

void propagate(point *p, char curr_player, char color, bool *change)
{
    point pvoisin;
    for (int k = 0; k < 4; k++)
    {
        pvoisin.x = p->x + direction[k].x;
        pvoisin.y = p->y + direction[k].y;
        bool in_bounds = (pvoisin.x >= 0 && pvoisin.x < BOARD_SIZE && pvoisin.y >= 0 && pvoisin.y < BOARD_SIZE);
        bool chosen_color = (get_cell(pvoisin.x, pvoisin.y) == color);
        if (in_bounds && chosen_color)
        {
            *change = true;
            set_cell(pvoisin.x, pvoisin.y, curr_player);
            propagate(&pvoisin, curr_player, color, change);
        }
    }
}

bool bad_update_board(char curr_player, char color)
{
    bool change = true;
    point *p = (point *)malloc(sizeof(point));
    while (change)
    {
        change = false;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (get_cell(i, j) == curr_player)
                {
                    p->x = i;
                    p->y = j;
                    propagate(p, curr_player, color, &change);
                }
            }
        }
    }
    free(p);
    return true;
}

// void visit_bfs(point *p, bool *seen, queue *q, char player)
// {
//     if (!seen[p->x + p->y * BOARD_SIZE])
//     {
//         seen[p->x + p->y * BOARD_SIZE] = true;
//         add_queue(q, p);
//     }
// }

// void update_board_bfs(char player, char color)
// {
//     bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
//     queue *q = create_queue();
//     if (player == player1)
//         add_queue(q, &start1);
//     else if (player == player2)
//         add_queue(q, &start2);
//     // TODO
//     int x, y;
//     point *p = (point *)malloc(sizeof(point));
//     while (!empty_queue(q))
//     {
//         pop_queue(q, p);
//         visit_bfs(p, seen, q, player);
//         // if (get_cell(p->x, p->y) == player)
//         // {
//         //     for (int k = 0; k < 4; k++)
//         //     {
//         //         x = p->x + direction[k].x;
//         //         y = p->y + direction[k].y;
//         //         bool in_bounds = (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
//         //         bool chosen_color = (get_cell(x, y) == color);
//         //         if (in_bounds && chosen_color)
//         //         {
//         //             set_cell(x, y, player);
//         //         }
//         //     }
//         // }
//     }
//     free(p);
//     free(q);
// }

bool in_colors(char c)
{
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (c == colors[i])
            return true;
    }
    return false;
}

/*main game function, contains the game cycle
 return the number of the winning player*/
int run_game()
{
    char c;
    char curr_player = player1;
    int tour = 1;
    bool game_running = true;
    // game cycle
    while (game_running)
    {
        print_board(curr_player, tour);
        c = get_player_move();
        game_running = bad_update_board(curr_player, c); // renvoie false ssi la partie est terminée
        change_player(&curr_player, &tour);
        system("clear"); // efface la console
    }
    return (tour & 1); // équivalent de %2 demandant beaucoup moins de calcul
}

char get_player_move()
{
    char c = '\0';
    bool lettreAutorisee = false;
    while (!lettreAutorisee)
    {
        printf("quelle couleur voulez vous jouer ? couleurs possibles : R, V, B, J, G, M, C\n");
        scanf(" %c", &c);
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("entree non valide, veuilliez entrer une valeur parmis les couleurs possibles");
    }
    return c;
}

void change_player(char *curr_player, int *tour)
{
    if (*curr_player == player1)
        *curr_player = player2;
    else
    {
        *curr_player = player1;
        (*tour)++;
    }
}

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
void print_board(char curr_player, int tour)
{
    system("clear");
    printf("tour %d : a %c de jouer\n", tour, curr_player);
    printf("Current board state :\n");
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            char c = get_cell(i, j);
            if (c == player1 || c == player2)
                printf("%c", c);
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
    printf("le joueur %d gagne !", winner);
}

/************ The tests **************/

/* Tests that the initialization works */
SUT_TEST(init_cell)
{
    char c = get_cell(5, 5);
    SUT_CHAR_EQUAL(c, '\0', "Creating the board does not initialize the cells to '\\0' but to '%c'", c);

    return 1;
}

/* Tests that the get_cell and set_cell work */
SUT_TEST(getset_cell)
{
    char c;

    set_cell(5, 5, 'A');
    c = get_cell(5, 5);
    SUT_CHAR_EQUAL(c, 'A', "Setting a cell to 'A' leads to '%c' as a value instead", c);

    return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(init_cell),
    SUT_TEST_SUITE_ADD(getset_cell),
    SUT_TEST_SUITE_END};
