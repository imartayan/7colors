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
    printf("2: Partie contre une IA stupide\n");
    printf("3: Partie contre une IA aléatoire\n");
    printf("4: Partie contre une IA gloutonne\n");
    while (n < 1 || n > 4)
    {
        printf("Quel est votre choix ?\n");
        scanf("%d", &n);
        clear_buffer();
        if (n < 1 || n > 4)
            printf("Entree incorecte, veuillez reessayer.\n");
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

char get_player_move()
{
    char c = '\0';
    bool lettreAutorisee = false;
    while (!lettreAutorisee)
    {
        printf("Quelle couleur voulez-vous jouer ? Choix possibles : ");
        for (int k = 0; k < NB_COLORS; k++)
        {
            set_print_color(colors[k]);
            printf("%c ", colors[k]);
            reset_print_color();
        }
        printf("\n");
        c = getchar();
        clear_buffer();
        lettreAutorisee = in_colors(c);
        if (!lettreAutorisee)
            printf("Entree non valide, veuillez entrer une valeur parmis les couleurs possibles.\n");
    }
    return c;
}

// ask if the user wants to play a new game
bool ask_new_game()
{
    char c = 'A';
    while (c != 'O' && c != 'o' && c != 'N' && c != 'n')
    {
        printf("Voulez-vous jouer une nouvelle partie ? (O / N)\n");
        c = getchar();
        clear_buffer();
        if (c != 'O' && c != 'o' && c != 'N' && c != 'n')
            printf("Entree non valide, veuillez entrer  O ou N.\n");
    }
    return (c == 'O' || c == 'o');
}
