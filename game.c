#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "display.h"
#include "game.h"
#include "AI.h"

void clear_buffer(){
  char c;
  // vider le buffer
  while((c = getchar()) != '\n' && c != EOF){}
}

int choose_game_mode(){
  int n = 0;
  while(n != 1 && n != 2){
    printf("Combien de joueurs ? (1 / 2)\n");
    scanf(" %d", &n);
    clear_buffer();
    if(n != 1 && n != 2)
      printf("Entree incorecte, veuillez reessayer");
  }
  return n;
}

/*main game function, contains the game cycle
 return the number of the winning player*/
int run_two_players_game(int* score1, int* score2)
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
        // on vérifie si il y a victoire avant de changer de joueur et de passer le tour
        if(2 * *score1 > NB_CASES || 2 * *score2 > NB_CASES)
          break;
        // on signale une égalité par le renvoi de 0
        if(2 * *score1 == NB_CASES && 2 * *score2 == NB_CASES)
          return 0;
        change_player(&curr_player, &tour);
        system("clear"); // efface la console
    }
    return ((tour & 1) + 1); // équivalent de %2 demandant beaucoup moins de calcul
}

int run_single_player_game(int *score1, int* score2){
    char color;
    int tour = 1;
    // game cycle
    while (2 * *score1 <= NB_CASES)
    {
        print_board(PLAYER1, tour, *score1, *score2);
        color = get_player_move();
        printf("B");
        update_board_bfs(PLAYER1, color, score1, score2);
        printf("C");
        if(2 * *score1 <= NB_CASES){
          printf("D");
          // AI's turn
          color = get_AI_move();
          update_board_bfs(PLAYER2, color, score1, score2);
          //system("clear"); // efface la console
          // the AI wins
          if(2 * *score2 > NB_CASES)
            return 2;
        }
        else if(2 * *score1 == NB_CASES && 2 * *score2 == NB_CASES)
          return 0;
        printf("E");
        system("clear"); // efface la console
        tour++;
    }
    printf("F");
    // the player wins
    return 1; // équivalent de %2 demandant beaucoup moins de calcul
}

bool in_colors(char c)
{
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (c == colors[i])
            return true;
    }
    return false;
}

char get_player_move()
{
    char c = '\0';
    bool lettreAutorisee = false;
    while (!lettreAutorisee)
    {
        printf("Quelle couleur voulez-vous jouer ? Choix possibles : R, V, B, J, G, M, C\n");
        scanf(" %c", &c);
        clear_buffer();
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("Entree non valide, veuillez entrer une valeur parmis les couleurs possibles");
    }
    printf("PORQUE ?");
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

// ask if the user wants to play a new game
bool new_game(){
  char c = 'A';
  while(c != 'O' && c != 'o' && c != 'N' && c != 'n'){
    printf("Voulez vous jouer une nouvelle partie ? (O / N)\n");
    scanf(" %c", &c);
    clear_buffer();
    if(c != 'O' && c != 'o' && c != 'N' && c != 'n')
      printf("Entree non valide, veuillez entrer  O ou N");
  }
  if(c == 'O' || c == 'o')
    return true;
  return false;
}
