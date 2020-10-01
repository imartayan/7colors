/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Implentation of the board module */

#include <stdio.h>   /* Import printf */
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"   /* Enforce that the header file matches the declarations */
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
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

int score1 = 0, score2 = 0;

const char colors[] = {'R', 'V', 'B', 'J', 'G', 'M', 'C'};
struct point direction[] = {{-1,0},{0,1}, {1,0}, {0, -1}};

/** Retrieves the color of a given board cell */
char get_cell(int x, int y){
    return board[y * BOARD_SIZE + x];
}


/** Changes the color of a given board cell */
void set_cell(int x, int y, char color){
    board[y * BOARD_SIZE + x] = color;
}

// init the board with random colors
void init_board(){
  int n;
  char color;
  for(int i =0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      n = rand()% NB_COLORS;
      color = colors[n];
      set_cell(i,j, color);
    }
  }
  set_cell(0,  BOARD_SIZE - 1, '2');
  set_cell(BOARD_SIZE - 1, 0, '1');
}

void update_board(char curr_player, char color){
  bool changement = true;
  int x, y;
  while(changement) {
    changement = false;
    for(int i = 0; i < BOARD_SIZE; i++){
      for(int j = 0; j < BOARD_SIZE; j++){
        if(get_cell(i, j) == curr_player){
          for(int k = 0; k < 4; k++){
            x = i + direction[k].x;
            y = j + direction[k].y;
            bool in_bounds = (x  >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
            bool chosen_color = (get_cell(x, y) == color);
            if(in_bounds && chosen_color ){
              set_cell(x, y, curr_player);
              changement = true;
            }
          }
        }
      }
    }
  }
}


void reset_print_color(){
  printf("\033[0m");
}

void set_print_color(char c){
  switch (c) {
    case 'R' :
      //rouge
      printf("\033[0;31m");
      break;

    case 'V' :
      //vert
      printf("\033[0;32m");
      break;

    case 'B' :
      //bleu
      printf("\033[0;34m");
      break;

    case 'J' :
      //jaune
      printf("\033[0;33m");
      break;

    case 'G' :
      // gris/blanc (couleur de départ)
      break;

    case 'M' :
      // magenta
      printf("\033[0;35m");
      break;

    case 'C' :
      // cyan
      printf("\033[0;36m");
      break;

    default :
      reset_print_color();
  }
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void){
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
          char c = get_cell(i,j);
          if(c == '1' || c == '2')
            printf("%c ",c);
          else{
            set_print_color(c);
            printf("%c ", 219);
            reset_print_color();
          }
        }
        printf("\n");
    }
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
    SUT_TEST_SUITE_END
};
