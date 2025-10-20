#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

// FONCTIONS DE BASE DU JEU
void init_board(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';
}

void print_board(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

int check_win(char board[3][3], char p) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
            return 1;
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p)
            return 1;
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return 1;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return 1;
    return 0;
}

// FONCTIONS DU BOT
int find_winning_move(char board[3][3], char player, int *out_r, int *out_c) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '.') {
                board[i][j] = player;
                int win = check_win(board, player);
                board[i][j] = '.';
                if (win) {
                    *out_r = i;
                    *out_c = j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int computer_try_win(char board[3][3], char computer, int *r, int *c) {
    return find_winning_move(board, computer, r, c);
}

int computer_block(char board[3][3], char human, int *r, int *c) {
    return find_winning_move(board, human, r, c);
}

int computer_take_center(char board[3][3], char computer, int *r, int *c) {
    if (board[1][1] == '.') {
        board[1][1] = computer;
        *r = 1; *c = 1;
        return 1;
    }
    return 0;
}

int computer_take_opposite_corner(char board[3][3], char human, char comp, int *r, int *c) {
    if (board[0][0] == human && board[2][2] == '.') { *r = 2; *c = 2; }
    else if (board[0][2] == human && board[2][0] == '.') { *r = 2; *c = 0; }
    else if (board[2][0] == human && board[0][2] == '.') { *r = 0; *c = 2; }
    else if (board[2][2] == human && board[0][0] == '.') { *r = 0; *c = 0; }
    else return 0;
    board[*r][*c] = comp;
    return 1;
}

int computer_take_any_corner(char board[3][3], char comp, int *r, int *c) {
    int corners[4][2];
    int cn = 0;
    int corner_coords[4][2] = { {0,0}, {0,2}, {2,0}, {2,2} };
    for (int i = 0; i < 4; ++i) {
        int rr = corner_coords[i][0], cc = corner_coords[i][1];
        if (board[rr][cc] == '.') {
            corners[cn][0] = rr; corners[cn][1] = cc; cn++;
        }
    }
    if (cn == 0) return 0;
    int pick = rand() % cn;
    *r = corners[pick][0]; *c = corners[pick][1];
    board[*r][*c] = comp;
    return 1;
}

int computer_take_any_side(char board[3][3], char comp, int *r, int *c) {
    int sides[4][2];
    int sn = 0;
    int side_coords[4][2] = { {0,1}, {1,0}, {1,2}, {2,1} };
    for (int i = 0; i < 4; ++i) {
        int rr = side_coords[i][0], cc = side_coords[i][1];
        if (board[rr][cc] == '.') {
            sides[sn][0] = rr; sides[sn][1] = cc; sn++;
        }
    }
    if (sn == 0) return 0;
    int pick = rand() % sn;
    *r = sides[pick][0]; *c = sides[pick][1];
    board[*r][*c] = comp;
    return 1;
}

int computer_fallback(char board[3][3], char comp, int *r, int *c) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '.') {
                board[i][j] = comp;
                *r = i; *c = j;
                return 1;
            }
        }
    }
    return 0;
}

void computer_move(char board[3][3], char computer) {
    char human = (computer == 'o') ? 'x' : 'o';
    int r = -1, c = -1;
    if (computer_try_win(board, computer, &r, &c)) {
        board[r][c] = computer;
        printf("Ordinateur joue en %d %d (gagnant)\n", r, c);
        return;
    }
    if (computer_block(board, human, &r, &c)) {
        board[r][c] = computer;
        printf("Ordinateur joue en %d %d (bloque)\n", r, c);
        return;
    }
    if (computer_take_center(board, computer, &r, &c)) {
        printf("Ordinateur joue en %d %d (centre)\n", r, c);
        return;
    }
    if (computer_take_opposite_corner(board, human, computer, &r, &c)) {
        printf("Ordinateur joue en %d %d (coin opposé)\n", r, c);
        return;
    }
    if (computer_take_any_corner(board, computer, &r, &c)) {
        printf("Ordinateur joue en %d %d (coin)\n", r, c);
        return;
    }
    if (computer_take_any_side(board, computer, &r, &c)) {
        printf("Ordinateur joue en %d %d (côté)\n", r, c);
        return;
    }
    if (computer_fallback(board, computer, &r, &c)) {
        printf("Ordinateur joue en %d %d (fallback)\n", r, c);
        return;
    }
}

// SAUVEGARDE / CHARGEMENT
void save_game(char board[3][3], char current, int moves) {
    FILE *f = fopen("save.txt", "w");
    if (!f) {
        perror("Erreur lors de la sauvegarde");
        return;
    }
    fprintf(f, "%c\n", current);
    fprintf(f, "%d\n", moves);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(f, "%c ", board[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int load_game(char board[3][3], char *current, int *moves) {
    FILE *f = fopen("save.txt", "r");
    if (!f) return 0;
    if (fscanf(f, " %c", current) != 1) { fclose(f); return 0; }
    if (fscanf(f, "%d", moves) != 1) { fclose(f); return 0; }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (fscanf(f, " %c", &board[i][j]) != 1) {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}


// INTERACTION JOUEUR
int player_move(char board[3][3], char human) {
    char line[128];
    printf("Entrez votre coup (ligne colonne) 0-2 0-2, ou 'q' pour quitter et sauvegarder: ");
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Erreur de lecture.\n");
        return 0;
    }
    // skip leading spaces
    char *p = line;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '\n' || *p == '\0') {
        printf("Entrée vide.\n");
        return 0;
    }
    if (*p == 'q' || *p == 'Q') {
        // signaler au caller que le joueur veut quitter et sauvegarder
        return -1;
    }
    int r, c;
    if (sscanf(p, "%d %d", &r, &c) != 2) {
        printf("Entrée invalide.\n");
        return 0;
    }
    if (r < 0 || r > 2 || c < 0 || c > 2) {
        printf("Coordonnées hors limites.\n");
        return 0;
    }
    if (board[r][c] != '.') {
        printf("Case occupée.\n");
        return 0;
    }
    board[r][c] = human;
    printf("Vous jouez en %d %d\n", r, c);
    return 1;
}

// BOUCLE PRINCIPALE JEUX
void tic_tac_toe() {
    char board[3][3];
    char current;
    int moves = 0;
    const char player = 'x', computer = 'o';

    printf("Souhaitez-vous charger une partie sauvegardée ? (o/n) : ");
    char rep;
    if (scanf(" %c", &rep) != 1) {
        printf("Erreur de lecture. Valeur par défaut : n\n");
        rep = 'n';
    }
    // vider le reste de la ligne pour que fgets fonctionne correctement ensuite
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (rep == 'o' && load_game(board, &current, &moves)) {
        printf("Partie chargée avec succès !\n");
        print_board(board);
    } else {
        init_board(board);
        srand((unsigned)time(NULL));
        current = (rand() % 2 == 0) ? player : computer;
        printf(current == player ? "Vous commencez (x).\n" : "Le BOT commence (o).\n");
    }

    while (moves < 9) {
        int moved = 0;
        if (current == player) moved = player_move(board, player);
        else { computer_move(board, computer); moved = 1; }

        if (moved == -1) {
            // le joueur a demandé à quitter : sauvegarder l'état actuel et quitter
            save_game(board, current, moves);
            printf("Partie sauvegardée. Vous pouvez la recharger plus tard.\n");
            return;
        }

        if (!moved) continue;
        moves++;
        print_board(board);

        save_game(board, current, moves);

        if (check_win(board, current)) {
            printf(current == player ? "Vous gagnez !\n" : "Le BOT gagne !\n");
            remove("save.txt");
            return;
        }

        current = (current == player) ? computer : player;
    }

    printf("Match nul !\n");
    remove("save.txt");
}


int main(void) {
    tic_tac_toe();
    return 0;
}
