#include <stdio.h>
#include "input.h"
#include "utils.h"
#include "display.h"

void clear_buffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int ask_int(int lower_bound, int upper_bound)
{
    int n = 0;
    while (n < lower_bound || n > upper_bound)
    {
        printf("Quel est votre choix ? ");
        scanf("%d", &n);
        clear_buffer();
        if (n < lower_bound || n > upper_bound)
            printf("Entrée incorecte, veuillez réessayer.\n");
    }
    return n;
}

void choose_game_mode(int *mode)
{
    printf("Choix du mode de jeu :\n");
    printf("1: Partie normale\n");
    printf("2: Tournoi de 100 parties\n");
    mode[0] = ask_int(1, 2);
    for (int i = 1; i < 3; i++)
    {
        if (i == 1)
            set_print_color(PLAYER1);
        else
            set_print_color(PLAYER2);
        printf("\nChoix du joueur %d :\n", i);
        printf("1: Humain\n");
        printf("2: IA aveugle\n");
        printf("3: IA aléatoire\n");
        printf("4: IA gloutonne\n");
        printf("5: IA hégémonique (sans bords)\n");
        printf("6: IA hégémonique (avec bords)\n");
        mode[i] = ask_int(1, 6);
    }
    reset_print_color();
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

char to_uppercase(char c)
{
    if ('a' <= c && c <= 'z')
        return c + 'A' - 'a';
    return c;
}

char ask_player_move()
{
    char c;
    bool lettreAutorisee = false;
    while (!lettreAutorisee)
    {
        printf("Quelle couleur voulez-vous jouer ? (Choix possibles :");
        for (int k = 0; k < NB_COLORS; k++)
        {
            set_print_color(colors[k]);
            printf(" %c", colors[k]);
        }
        reset_print_color();
        printf(") ");
        c = to_uppercase(getchar());
        clear_buffer();
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("Entrée non valide, veuillez entrer une valeur parmis les couleurs possibles.\n");
    }
    return c;
}

// ask if the user wants to play a new game
bool ask_new_game()
{
    char c = 'A';
    while (c != 'O' && c != 'o' && c != 'N' && c != 'n')
    {
        printf("Voulez-vous jouer une nouvelle partie ? (O / N) ");
        c = to_uppercase(getchar());
        clear_buffer();
        if (c != 'O' && c != 'N')
            printf("Entrée non valide, veuillez entrer O ou N.\n");
    }
    return (c == 'O');
}
