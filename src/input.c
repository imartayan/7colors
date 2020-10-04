#include "input.h"

void clear_buffer()
{
    char c;
    // vider le buffer
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int choose_game_mode()
{
    int n = 0;
    printf("Choix du mode :\n");
    printf("1: Partie à deux joueurs\n");
    printf("2: Partie contre une IA aveugle\n");
    printf("3: Partie contre une IA aléatoire\n");
    printf("4: Partie contre une IA gloutonne\n");
    printf("5: Partie contre une IA hégémonique sans bord\n");
    printf("6: Partie entre IA aléatoire et gloutonne\n");
    printf("7: Partie entre IA gloutonne et hégémonique sans bord\n");
    printf("8: Partie entre IA gloutonne et hégémonique avec bord\n");
    printf("9: Partie entre IA hégémonique sans bord et avec bord\n");
    printf("10: Parties rapides entre IA sans bord et avec bord\n");
    while (n < 1 || n > 10)
    {
        printf("Quel est votre choix ?\n");
        scanf("%d", &n);
        clear_buffer();
        if (n < 1 || n > 10)
            printf("Entrée incorecte, veuillez réessayer.\n");
    }
    return n;
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

char ask_player_move()
{
    char c = '\0';
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
        c = getchar();
        clear_buffer();
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("Entrée non valide, veuillez entrer une valeur parmis les couleurs possibles.\n");
    }
    return c;
}

char get_player_move(char player)
{
    return ask_player_move();
}

// ask if the user wants to play a new game
bool ask_new_game()
{
    char c = 'A';
    while (c != 'O' && c != 'o' && c != 'N' && c != 'n')
    {
        printf("Voulez-vous jouer une nouvelle partie ? (O / N) ");
        c = getchar();
        clear_buffer();
        if (c != 'O' && c != 'o' && c != 'N' && c != 'n')
            printf("Entrée non valide, veuillez entrer O ou N.\n");
    }
    return (c == 'O' || c == 'o');
}
