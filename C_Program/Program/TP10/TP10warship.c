#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define GRID_SIZE 10
#define NUM_SHIPS 5
#define SAVE_FILE "savegame.txt"

static const int ship_sizes[NUM_SHIPS] = {5,4,3,3,2};
static const char *ship_names[NUM_SHIPS] = {
    "Porte-avions","Croiseur","Contre-torpilleur",
    "Sous-marin","Torpilleur"
};

//===========================FUNCTION PROTOTYPES==============================//

static void init_grid(char g[GRID_SIZE][GRID_SIZE]);
static void print_col_headers(void);
static void print_grid(const char g[GRID_SIZE][GRID_SIZE], int reveal);
static int can_place(const char g[GRID_SIZE][GRID_SIZE],
                     int r, int c, char ori, int size);
static void do_place(char g[GRID_SIZE][GRID_SIZE],
                     int r, int c, char ori, int size);
__attribute__((unused)) static void clear_input_line(void);

static int save_exists(void);
static int save_game(const char *filename,
                     const char g1[GRID_SIZE][GRID_SIZE],
                     const char g2[GRID_SIZE][GRID_SIZE],
                     int current);
static int load_game(const char *filename,
                     char g1[GRID_SIZE][GRID_SIZE],
                     char g2[GRID_SIZE][GRID_SIZE],
                     int *current);
static void remove_save(void);
static int remaining_ship_cells(const char g[GRID_SIZE][GRID_SIZE]);
static int save_current(const char *file,
                        const char own[GRID_SIZE][GRID_SIZE],
                        const char opp[GRID_SIZE][GRID_SIZE],
                        int current);

static int ask_yes(const char *prompt);

static int place_single_ship(char g[GRID_SIZE][GRID_SIZE], int player, int s);
static int pause_after_placement(void);
static int place_ships_for_player(char g[GRID_SIZE][GRID_SIZE], int player);

static int process_single_shot(char own[GRID_SIZE][GRID_SIZE],
                               char opp[GRID_SIZE][GRID_SIZE],
                               int current, int *win);
static int player_turn(char own[GRID_SIZE][GRID_SIZE],
                       char opp[GRID_SIZE][GRID_SIZE],
                       int current, int *win);

static int setup_game(char g1[GRID_SIZE][GRID_SIZE],
                      char g2[GRID_SIZE][GRID_SIZE],
                      int *current_player);
                      
static int quit_requested = 0;

//===========================================================================//


// Initialise la grille en remplissant chaque case par un espace
static void init_grid(char g[GRID_SIZE][GRID_SIZE]){
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
            g[i][j] = ' ';
}

// Affiche les en-têtes de colonnes (1..GRID_SIZE)
static void print_col_headers(void){
    printf("   ");
    for(int c=1;c<=GRID_SIZE;c++)
        printf(" %2d", c);
    printf("\n");
}

// Affiche la grille; reveal==1 montre les navires, sinon non
static void print_grid(const char g[GRID_SIZE][GRID_SIZE], int reveal){
    print_col_headers();
    for(int i=0;i<GRID_SIZE;i++){
        printf("%2d ", i+1);
        for(int j=0;j<GRID_SIZE;j++){
            char ch = g[i][j];
            if(!reveal && ch == 'N') ch = ' ';
            char d = (ch == ' ') ? '.' : ch;
            printf("|%c", d);
        }
        printf("|\n");
    }
}


// Vérifie si un navire peut être placé aux coordonnées données

//c = colonne , r = ligne , ori = orientation
static int can_place(const char g[GRID_SIZE][GRID_SIZE],
                     int r, int c, char ori, int size){
    if(ori == 'h'){
        if(c + size > GRID_SIZE) return 0;
        for(int j=c;j<c+size;j++) if(g[r][j] != ' ') return 0;
    } else {
        if(r + size > GRID_SIZE) return 0;
        for(int i=r;i<r+size;i++) if(g[i][c] != ' ') return 0;
    }
    return 1;
}

// Place un navire ('N') horizontalement ou verticalement
static void do_place(char g[GRID_SIZE][GRID_SIZE],
                     int r, int c, char ori, int size){
    if(ori == 'h'){
        for(int j=c;j<c+size;j++) g[r][j] = 'N';
    } else {
        for(int i=r;i<r+size;i++) g[i][c] = 'N';
    }
}

// Vide la ligne d'entrée stdin jusqu'à '\n' ou EOF
__attribute__((unused)) static void clear_input_line(void){
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}


// Vérifie si un fichier de sauvegarde existe
static int save_exists(void){
    FILE *f = fopen(SAVE_FILE, "rb");
    if(f){ fclose(f); return 1; }
    return 0;
}

// Sauvegarde deux grilles et l'ordre courant dans un fichier
static int save_game(const char *filename,
                     const char g1[GRID_SIZE][GRID_SIZE],
                     const char g2[GRID_SIZE][GRID_SIZE],
                     int current){
    FILE *f = fopen(filename, "wb");
    if(!f) return 0;
    size_t total = (size_t)GRID_SIZE * GRID_SIZE;
    if(fwrite(&g1[0][0], sizeof(char), total, f) != total){
        fclose(f); return 0;
    }
    if(fwrite(&g2[0][0], sizeof(char), total, f) != total){
        fclose(f); return 0;
    }
    if(fwrite(&current, sizeof(current), 1, f) != 1){
        fclose(f); return 0;
    }
    fclose(f); return 1;
}

// Charge deux grilles et l'ordre courant depuis un fichier
static int load_game(const char *filename,
                     char g1[GRID_SIZE][GRID_SIZE],
                     char g2[GRID_SIZE][GRID_SIZE],
                     int *current){
    FILE *f = fopen(filename, "rb");
    if(!f) return 0;
    size_t total = (size_t)GRID_SIZE * GRID_SIZE;
    if(fread(&g1[0][0], sizeof(char), total, f) != total){
        fclose(f); return 0;
    }
    if(fread(&g2[0][0], sizeof(char), total, f) != total){
        fclose(f); return 0;
    }
    if(fread(current, sizeof(*current), 1, f) != 1){
        fclose(f); return 0;
    }
    fclose(f); return 1;
}

// Supprime le fichier de sauvegarde s'il existe
static void remove_save(void){
    (void) remove(SAVE_FILE);
}

// Compte les cases de navire ('N') restantes dans la grille
static int remaining_ship_cells(const char g[GRID_SIZE][GRID_SIZE]){
    int cnt = 0;
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
            if(g[i][j] == 'N') cnt++;
    return cnt;
}

// Sauvegarde en respectant l'ordre actuel des joueurs
static int save_current(const char *file,
                        const char own[GRID_SIZE][GRID_SIZE],
                        const char opp[GRID_SIZE][GRID_SIZE],
                        int current){
    if(current == 1)
        return save_game(file, own, opp, current);
    return save_game(file, opp, own, current);
}

// Pose une question oui/non et retourne 1 pour 'o', 0 sinon
static int ask_yes(const char *prompt){
    char ans[16];
    printf("%s", prompt);
    if(!fgets(ans, sizeof ans, stdin)) return -1;
    char *q = ans; while(*q==' '||*q=='\t') q++;
    return (*q=='o' || *q=='O') ? 1 : 0;
}

// Demande au joueur de placer un navire unique
static int place_single_ship(char g[GRID_SIZE][GRID_SIZE], int player,
                             int s){
    (void) player;
    char line[128];
    int size = ship_sizes[s];
    while(1){
        int r, c; char ori;
        printf("Placer %s (%d cases). Entrez ligne colonne "
               "orientation(h/v) (ou 'q' pour quitter) : ",
               ship_names[s], size);
        if(!fgets(line, sizeof line, stdin)){
            quit_requested = 1; return 1;
        }
        char *p = line; while(*p==' '||*p=='\t') p++;
        if(*p=='q' || *p=='Q'){
            quit_requested = 1;
            printf("Abandon demandé. Fin du placement.\n");
            return 1;
        }
        if(sscanf(p, "%d %d %c", &r, &c, &ori) != 3){
            printf("Entrée invalide. Réessayer.\n"); continue;
        }
        r--; c--;
        if(r<0||r>=GRID_SIZE||c<0||c>=GRID_SIZE||
           (ori!='h'&&ori!='v'&&ori!='H'&&ori!='V')){
            printf("Coordonnées ou orientation invalides. "
                   "(1..%d, h/v)\n", GRID_SIZE);
            continue;
        }
        ori = (ori=='H') ? 'h' : (ori=='V') ? 'v' : ori;
        if(!can_place(g, r, c, ori, size)){
            printf("Placement impossible (dépassement ou collision). "
                   "Réessayer.\n");
            continue;
        }
        do_place(g, r, c, ori, size);
        print_grid(g, 1);
        break;
    }
    return 0;
}

// Pause après placement et attend Entrée ou 'q' pour quitter
static int pause_after_placement(void){
    char line[128];
    printf("Placement terminé. Appuyez sur Entrée pour continuer...");
    if(!fgets(line, sizeof line, stdin)){ quit_requested = 1; return 1; }
    char *p2 = line; while(*p2==' '||*p2=='\t') p2++;
    if(*p2=='q' || *p2=='Q'){
        quit_requested = 1;
        printf("Abandon demandé. Fin du placement.\n"); return 1;
    }
    printf("\033[2J\033[H");
    return 0;
}

// Effectue le placement de tous les navires pour un joueur
static int place_ships_for_player(char g[GRID_SIZE][GRID_SIZE], int player){
    printf("\n=== Placement des navires pour le joueur %d ===\n", player);
    print_grid(g, 1);
    for(int s=0;s<NUM_SHIPS;s++){
        if(place_single_ship(g, player, s)) return 1;
        if(quit_requested) return 1;
    }
    if(pause_after_placement()) return 1;
    return 0;
}

// Traite un tir: sauvegarde, quitter, touche/eau et vérifie victoire
static int process_single_shot(char own[GRID_SIZE][GRID_SIZE],
                               char opp[GRID_SIZE][GRID_SIZE],
                               int current, int *win){
    char line[128];
    printf("Entrez coordonnées du tir (ligne colonne) "
           "(ou 'q' pour quitter, 's' pour sauvegarder) : ");
    if(!fgets(line, sizeof line, stdin)){ quit_requested = 1; return -1; }
    char *p = line; while(*p==' '||*p=='\t') p++;
    if(*p=='q' || *p=='Q'){
        int a = ask_yes("Sauvegarder la partie avant de quitter ? (o/n): ");
        if(a==1){
            if(save_current(SAVE_FILE, own, opp, current))
                printf("Partie sauvegardée dans '%s'.\n", SAVE_FILE);
            else printf("Échec de la sauvegarde.\n");
        } else if(a==-1){ quit_requested = 1; return -1; }
        quit_requested = 1;
        printf("Abandon demandé. Fin de la partie.\n");
        return -1;
    }
    if(*p=='s' || *p=='S'){
        if(save_current(SAVE_FILE, own, opp, current)){
            printf("Partie sauvegardée dans '%s'. Fin du programme.\n",
                   SAVE_FILE);
            quit_requested = 1; return -1;
        } else {
            printf("Échec de la sauvegarde. Réessayer.\n"); return 2;
        }
    }
    int r,c;
    if(sscanf(p, "%d %d", &r, &c) != 2){
        printf("Entrée invalide. Réessayer.\n"); return 2;
    }
    r--; c--;
    if(r<0||r>=GRID_SIZE||c<0||c>=GRID_SIZE){
        printf("Coordonnées hors de la grille. (1..%d)\n", GRID_SIZE);
        return 2;
    }
    char cell = opp[r][c];
    if(cell == 'X' || cell == 'o'){
        printf("Case déjà visée. Choisissez une autre case.\n"); return 2;
    }
    if(cell == 'N'){
        opp[r][c] = 'X';
        printf("Touché ! Tirez de nouveau !\n");
        if(remaining_ship_cells(opp) == 0){
            printf("\nJoueur %d a coulé tous les navires adverses. "
                   "Joueur %d gagne !\n", current, current);
            printf("Grille finale du perdant :\n"); print_grid(opp, 1);
            *win = 1; return 1;
        }
        return 1;
    }
    opp[r][c] = 'o';
    printf("Dans l'eau.\n"); return 0;
}

// Gère le tour d'un joueur avec répétition si touche
static int player_turn(char own[GRID_SIZE][GRID_SIZE],
                       char opp[GRID_SIZE][GRID_SIZE],
                       int current, int *win){
    printf("\n=== Tour du joueur %d ===\n", current);
    printf("Votre grille:\n"); print_grid(own, 1);
    printf("Grille adversaire (ce que vous connaissez):\n");
    print_grid(opp, 0);
    int extra_shot = 0;
        do{
        int res = process_single_shot(own, opp, current, win);
        if(res == -1) return 1;// quitter ou sauvegarder
        if(res == 2) continue;// mauvaise entrée, redemande

        if(*win) return 0;

        extra_shot = (res == 1);
        printf("Votre grille:\n"); print_grid(own, 1);
        printf("Grille adversaire (ce que vous connaissez):\n");
        print_grid(opp, 0);
    } while(extra_shot && !quit_requested);
    return 0;

}

// Charge ou initialise une nouvelle partie et place les navires
static int setup_game(char g1[GRID_SIZE][GRID_SIZE],
                      char g2[GRID_SIZE][GRID_SIZE],
                      int *current_player){
    if(save_exists()){
        int a = ask_yes("Une partie sauvegardée existe. La charger ? (o/n) : ");
        if(a == 1){
            if(load_game(SAVE_FILE, g1, g2, current_player)){
                printf("Partie chargée avec succès !\n"); return 0;
            }
            printf("Échec du chargement. Nouvelle partie.\n");
        } else if(a == -1){
            printf("Erreur de lecture. Fin du programme.\n"); return 1;
        }
    }
    init_grid(g1); init_grid(g2);
    if(place_ships_for_player(g1, 1)) return 1;
    if(place_ships_for_player(g2, 2)) return 1;
    return 0;
}

//===========================================================================//

int main(void){
    char grid1[GRID_SIZE][GRID_SIZE];
    char grid2[GRID_SIZE][GRID_SIZE];
    int current_player = 1;
    quit_requested = 0;
    printf("=== Bienvenue dans le jeu de la Bataille Navale ===\n");
    if(setup_game(grid1, grid2, &current_player)) return 0;
    while(!quit_requested){
        int win = 0;
        if(current_player == 1){
            if(player_turn(grid1, grid2, 1, &win)) break;
            if(win){ remove_save(); break; }
            current_player = 2;
        } else {
            if(player_turn(grid2, grid1, 2, &win)) break;
            if(win){ remove_save(); break; }
            current_player = 1;
        }
    }
    if(quit_requested){
        printf("Partie interrompue. Vous pouvez la recharger plus tard.\n");
    } else {
        printf("Au revoir.\n");
    }
    return 0;
}
