# 7colors
An implementation of the 7 colors game written in C.

![Preview](preview.png)

## Project structure
* `defaults.h` contains the defaults values for the number of colors, the size of the board...
* `structures.c` contains point, linked list and queue data structures
* `utils.c` contains some basic functions for reading or writing a cell, creating a random number...
* `display.c` contains functions for printing the board and the score
* `input.c` contains functions for asking game modes, next move...
* `board.c` contains functions for creating the board and updating it after each move
* `AI.c` contains different strategies for the artificial intelligence
* `game.c` contains functions for the different modes of the game
* `main.c` contains the main loop of the game

## Done
* generate the board
* naive search of accessible colors
* list and queue structure
* correctly handling colors
* better propagation function
* 2 players mode
* better update function using BFS
* single player mode with random player

## Todo
* create a greedy player
* create a tournament
* write documentation (duh)
* write a detailed report
* (improve artificial intelligence (minimax ?))

## Sources
* http://www.gecif.net/qcm/information/ascii_decimal_hexa.pdf
* http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
