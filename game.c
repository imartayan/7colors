#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "display.h"
#include "game.h"

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
int run_game(int* score1, int* score2)
{
    char color;
    char curr_player = PLAYER1;
    int tour = 1;
    // game cycle
    while (2 * *score1 <= NB_CASES && 2 * *score2 <= NB_CASES)
    {
        print_board(curr_player, tour, *score1, *score2);
        color = get_player_move();
        // bad_update_board(curr_player, color);
        update_board_bfs(curr_player, color, score1, score2);
        change_player(&curr_player, &tour);
        system("clear"); // efface la console
    }
    return ((tour & 1) + 1); // équivalent de %2 demandant beaucoup moins de calcul
}

char get_player_move()
{
    char c = '\0';
    bool lettreAutorisee = false;
    while (!lettreAutorisee)
    {
        printf("Quelle couleur voulez-vous jouer ? Choix possibles : R, V, B, J, G, M, C\n");
        scanf(" %c", &c);
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("Entree non valide, veuilliez entrer une valeur parmis les couleurs possibles");
    }
    return c;
}

void change_player(char *curr_player, int *tour)
{
    if (*curr_player == PLAYER1)
        *curr_player = PLAYER2;
    else
    {
        *curr_player = PLAYER1;
        (*tour)++;
    }
}
