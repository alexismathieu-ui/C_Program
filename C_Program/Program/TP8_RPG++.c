#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // Pour sleep()

// STRUCTURES DES PERSONNAGES

struct Player {
    char name[50];
    int health;
    int max_health;
    int attack;
    int defense;
    int level;
    int experience;
    int potions;
};

struct Goblin { int health; int max_health; int attack; int defense; };
struct Elf    { int health; int max_health; int attack; int defense; };
struct Orc    { int health; int max_health; int attack; int defense; };
struct Dragon { int health; int max_health; int attack; int defense; };

// === PROTOTYPES ===
void waves_of_enemies(struct Player* player, struct Goblin* goblin,
                      struct Elf* elf, struct Orc* orc, struct Dragon* dragon);
void handle_fight_menu_choice(int choice, struct Player* player,
                              struct Goblin* goblin, struct Elf* elf,
                              struct Orc* orc, struct Dragon* dragon);
void interactive_menu(struct Player* player, struct Goblin* goblin,
                      struct Elf* elf, struct Orc* orc,
                      struct Dragon* dragon);
void rest_player(struct Player* player);

// === FONCTIONS D’AFFICHAGE ===

void display_player(struct Player* player) {
    printf("\n");
    printf("Joueur: %s\n", player->name);
    printf("Santé: %d/%d\n", player->health, player->max_health);
    printf("Niveau: %d\n", player->level);
    printf("Expérience: %d\n", player->experience);
    printf("Potions: %d\n", player->potions);
    printf("\n");
}

void display_goblin(struct Goblin* goblin) {
    printf("Santé du Gobelin: %d/%d\n", goblin->health, goblin->max_health);
    printf("Attaque du Gobelin: %d\n", goblin->attack);
    printf("Défense du Gobelin: %d\n", goblin->defense);
    printf("\n");
}

void display_elf(struct Elf* elf) {
    printf("Santé de l'Elfe: %d/%d\n", elf->health, elf->max_health);
    printf("Attaque de l'Elfe: %d\n", elf->attack);
    printf("Défense de l'Elfe: %d\n", elf->defense);
    printf("\n");
}

void display_orc(struct Orc* orc) {
    printf("Santé de l'Orc: %d/%d\n", orc->health, orc->max_health);
    printf("Attaque de l'Orc: %d\n", orc->attack);
    printf("Défense de l'Orc: %d\n", orc->defense);
    printf("\n");
}

void display_dragon(struct Dragon* dragon) {
    printf("Santé du Dragon: %d/%d\n", dragon->health, dragon->max_health);
    printf("Attaque du Dragon: %d\n", dragon->attack);
    printf("Défense du Dragon: %d\n", dragon->defense);
    printf("\n");
}

// INITIALISATION DES PERSONNAGES

void init_player(struct Player* player) {
    printf("\nEntrez votre pseudonyme: ");
    scanf("%49s", player->name);
    player->max_health = 100;
    player->health = player->max_health;
    player->attack = 10;
    player->defense = 5;
    player->level = 1;
    player->experience = 0;
    player->potions = 3;
    printf("\nBienvenue, %s!\n\n", player->name);
}

void init_goblin(struct Goblin* goblin) {
    goblin->max_health = 50;
    goblin->health = goblin->max_health;
    goblin->attack = 8;
    goblin->defense = 3;
}

void init_elf(struct Elf* elf) {
    elf->max_health = 70;
    elf->health = elf->max_health;
    elf->attack = 12;
    elf->defense = 4;
}

void init_orc(struct Orc* orc) {
    orc->max_health = 80;
    orc->health = orc->max_health;
    orc->attack = 15;
    orc->defense = 6;
}

void init_dragon(struct Dragon* dragon) {
    dragon->max_health = 1500;
    dragon->health = dragon->max_health;
    dragon->attack = 35;
    dragon->defense = 25;
}

// FONCTIONS DE NIVEAU ET D'EXPÉRIENCE

void gain_experience(struct Player* player, int exp) {
    player->experience += exp;
    if (player->experience >= player->level * 100) {
        player->level++;
        player->max_health += 20;
        player->health = player->max_health;
        player->attack += 5;
        player->defense += 2;
        player->experience = 0;
        printf("\nFélicitations! Vous avez atteint le niveau %d!\n",
               player->level);
        printf("\n");
    }
}

void use_potion(struct Player* player) {
    if (player->potions > 0) {
        player->health += player->max_health / 2;
        if (player->health > player->max_health) {
            player->health = player->max_health;
        }
        player->potions--;
        printf("\n%s utilise une potion!\n", player->name);
        printf("Santé restaurée à %d/%d\n\n",
               player->health, player->max_health);
    } else {
        printf("\nPas de potions restantes!\n\n");
    }
}

void rest_player(struct Player* player) {
    int heal = player->max_health / 2;
    player->health += heal;
    if (player->health > player->max_health)
        player->health = player->max_health;
    printf("\n%s se repose et récupère %d points de santé.\n",
           player->name, heal);
    printf("Santé: %d/%d\n\n", player->health, player->max_health);
}

// MENUS

void fight_menu_choice(){
    printf("\n=== MENU DE COMBAT ===\n");
    printf("1. Attaquer\n");
    printf("2. Utiliser une potion\n");
    printf("3. Fuir\n");
    printf("4. Quitter\n");
    printf("Choisissez une option: ");
}

void handle_fight_menu_choice(int choice, struct Player* player,
                              struct Goblin* goblin, struct Elf* elf,
                              struct Orc* orc, struct Dragon* dragon) {
    switch (choice) {
        case 1:
            display_player(player);
            break;
        case 2:
            display_goblin(goblin);
            display_elf(elf);
            display_orc(orc);
            display_dragon(dragon);
            break;
        case 3:
            use_potion(player);
            break;
        case 4:
            printf("\nQuitter le jeu...\n\n");
            exit(0);
        default:
            printf("\nOption invalide. Veuillez réessayer.\n\n");
    }
}

// MENU INTERACTIF

void interactive_menu(struct Player* player, struct Goblin* goblin,
                      struct Elf* elf, struct Orc* orc,
                      struct Dragon* dragon) {
    int choice;
    while (1) {
        printf("=== MENU ===\n");
        printf("1. Afficher les statistiques du joueur\n");
        printf("2. Afficher les statistiques des ennemis\n");
        printf("3. Utiliser une potion\n");
        printf("4. Quitter le jeu\n");
        printf("5. Commencer les vagues d'ennemis\n");
        printf("6. Se reposer (récupère 50%% de la vie max)\n");
        printf("7. Aide\n");
        printf("Choisissez une option: ");

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nEntrée invalide. Veuillez entrer un nombre.\n\n");
            continue;
        }

        printf("\n");
        if (choice == 5) {
            waves_of_enemies(player, goblin, elf, orc, dragon);
        } else if (choice == 6) {
            rest_player(player);
        } else if (choice == 7) {
            printf("Aide: Utilisez les options pour gérer votre joueur.\n");
            printf("Commencez les vagues pour combat. Sauvegarde non "
                   "implémentée.\n\n");
        } else {
            handle_fight_menu_choice(choice, player, goblin, elf, orc,
                                     dragon);
        }

        printf("\n");
    }
}

// MÉCANIQUES DE JEU

static int spawn_enemies(struct Goblin* goblin, struct Elf* elf,
                         struct Orc* orc, int types[], int *count) {
    *count = 1 + rand() % 2; // 1 ou 2 ennemis
    if (*count == 1) {
        types[0] = rand() % 3;
    } else {
        types[0] = rand() % 3;
        do { types[1] = rand() % 3; } while (types[1] == types[0]);
    }
    for (int i = 0; i < *count; ++i) {
        switch (types[i]) {
            case 0:
                init_goblin(goblin);
                printf("Un Gobelin sauvage apparaît! (ID %d)\n", i+1);
                display_goblin(goblin);
                break;
            case 1:
                init_elf(elf);
                printf("Un Elfe sauvage apparaît! (ID %d)\n", i+1);
                display_elf(elf);
                break;
            case 2:
                init_orc(orc);
                printf("Un Orc sauvage apparaît! (ID %d)\n", i+1);
                display_orc(orc);
                break;
        }
    }
    return *count;
}

static int get_player_choice(void) {
    int choice;
    while (1) {
        fight_menu_choice();
        if (scanf("%d", &choice) == 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("\n");
            return choice;
        }
        int c; while ((c = getchar()) != '\n' && c != EOF);
        printf("\nEntrée invalide. Veuillez entrer un nombre.\n\n");
    }
}

static void print_enemy_status(int types[], int count, int alive[],
                               struct Goblin* goblin, struct Elf* elf,
                               struct Orc* orc) {
    for (int i = 0; i < count; ++i) {
        if (!alive[i]) continue;
        const char *name =
            (types[i] == 0) ? "Gobelin"
            : (types[i] == 1) ? "Elfe" : "Orc";
        int hp = (types[i] == 0) ? goblin->health
               : (types[i] == 1) ? elf->health : orc->health;
        int maxhp = (types[i] == 0) ? goblin->max_health
                  : (types[i] == 1) ? elf->max_health : orc->max_health;
        printf("%d. %s (ID %d) - Santé: %d/%d\n", i+1, name, i+1, hp, maxhp);
    }
    printf("\n");
}

static int choose_target(int types[], int count, int alive[],
                         struct Goblin* goblin, struct Elf* elf,
                         struct Orc* orc) {
    if (count == 1) return 0;
    print_enemy_status(types, count, alive, goblin, elf, orc);
    int t = 0;
    while (1) {
        printf("Entrez 1 ou 2: ");
        if (scanf("%d", &t) == 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            if (t >= 1 && t <= count && alive[t-1]) return t-1;
        } else {
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("Cible invalide. Réessayez.\n");
    }
}

static void apply_player_attack(struct Player* player, struct Goblin* goblin,
                                struct Elf* elf, struct Orc* orc,
                                int types[], int target, int alive[]) {
    int defense = 0;
    int *enemy_hp = NULL;
    switch (types[target]) {
        case 0: defense = goblin->defense; enemy_hp = &goblin->health; break;
        case 1: defense = elf->defense;    enemy_hp = &elf->health;    break;
        case 2: defense = orc->defense;    enemy_hp = &orc->health;    break;
    }
    int dmg = player->attack - defense;
    if (dmg < 1) dmg = 1;
    *enemy_hp -= dmg;
    if (*enemy_hp < 0) *enemy_hp = 0;
    printf("%s inflige %d dégâts à l'ennemi (ID %d).\n",
           player->name, dmg, target+1);
    printf("Santé restante: %d\n\n", *enemy_hp);
    if (*enemy_hp == 0 && alive[target]) {
        alive[target] = 0;
        if (types[target] == 0) {
            printf("Gobelin vaincu!\n\n");
            gain_experience(player, 150);
        } else if (types[target] == 1) {
            printf("Elfe vaincu!\n\n");
            gain_experience(player, 250);
        } else if (types[target] == 2) {
            printf("Orc vaincu!\n\n");
            gain_experience(player, 400);
        }
    }
}

static void enemies_attack(struct Player* player, struct Goblin* goblin,
                           struct Elf* elf, struct Orc* orc,
                           int types[], int count, int alive[]) {
    for (int i = 0; i < count; ++i) {
        if (!alive[i]) continue;
        int enemy_atk = 0;
        const char *ename = NULL;
        if (types[i] == 0) { enemy_atk = goblin->attack; ename = "Gobelin"; }
        else if (types[i] == 1) { enemy_atk = elf->attack; ename = "Elfe"; }
        else { enemy_atk = orc->attack; ename = "Orc"; }
        int dmg = enemy_atk - player->defense;
        if (dmg < 1) dmg = 1;
        player->health -= dmg;
        if (player->health < 0) player->health = 0;
        printf("%s (ID %d) inflige %d dégâts à %s.\n",
               ename, i+1, dmg, player->name);
        printf("Santé du joueur: %d/%d\n\n",
               player->health, player->max_health);
        if (player->health == 0) {
            printf("Vous êtes mort. Fin de la partie.\n");
            exit(0);
        }
    }
}

static void handle_encounter(struct Player* player, struct Goblin* goblin,
                             struct Elf* elf, struct Orc* orc,
                             struct Dragon* dragon) {
    int types[2];
    int count = 0;
    spawn_enemies(goblin, elf, orc, types, &count);
    int alive[2] = {0,0}; for (int i = 0; i < count; ++i) alive[i] = 1;
    while (player->health > 0) {
        int any_alive = 0; for (int i = 0; i < count; ++i) if (alive[i]) any_alive = 1;
        if (!any_alive) { printf("Tous les ennemis de la rencontre sont morts.\n\n"); break; }
        int choice = get_player_choice();
        if (choice == 1) {
            int target = choose_target(types, count, alive, goblin, elf, orc);
            apply_player_attack(player, goblin, elf, orc, types, target, alive);
        } else if (choice == 2) {
            use_potion(player);
        } else if (choice == 3) {
            printf("%s ne peut pas fuir la rencontre!\n", player->name);
            printf("Vous devez combattre jusqu'à la mort.\n\n");
        } else if (choice == 4) {
            printf("Quitter le jeu...\n\n"); exit(0);
        } else {
            printf("Option invalide. Veuillez réessayer.\n\n");
        }
        enemies_attack(player, goblin, elf, orc, types, count, alive);
        sleep(1);
    }
}

static void run_wave(struct Player* player, struct Goblin* goblin,
                     struct Elf* elf, struct Orc* orc,
                     struct Dragon* dragon, int wave) {
    printf("\n=== Vague %d ===\n\n", wave);
    for (int i = 0; i < wave; i++) {
        handle_encounter(player, goblin, elf, orc, dragon);
        if (player->health <= 0) { printf("Vous êtes mort. Fin de la partie.\n"); exit(0); }
    }
    printf("Fin de la vague %d!\n\n", wave);
    sleep(2);
}

static void handle_dragon_battle(struct Player* player, struct Goblin* goblin,
                                 struct Elf* elf, struct Orc* orc,
                                 struct Dragon* dragon) {
    printf("\nUn Dragon apparaît!\n\n");
    init_dragon(dragon);
    display_dragon(dragon);
    while (dragon->health > 0 && player->health > 0) {
        int choice = get_player_choice();
        if (choice == 1) {
            int dmg = player->attack - dragon->defense;
            if (dmg < 1) dmg = 1;
            dragon->health -= dmg;
            if (dragon->health < 0) dragon->health = 0;
            printf("%s inflige %d dégâts au Dragon.\n",
                   player->name, dmg);
            printf("Santé du Dragon: %d/%d\n\n", dragon->health,
                   dragon->max_health);
        } else if (choice == 2) {
            use_potion(player);
        } else if (choice == 3) {
            printf("%s tente de fuir... impossible face au Dragon !\n\n",
                   player->name);
        } else if (choice == 4) {
            printf("Quitter le jeu...\n\n"); exit(0);
        } else {
            printf("Option invalide. Veuillez réessayer.\n\n");
        }
        if (dragon->health > 0) {
            int dmg = dragon->attack - player->defense;
            if (dmg < 1) dmg = 1;
            player->health -= dmg;
            if (player->health < 0) player->health = 0;
            printf("Le Dragon attaque et inflige %d dégâts à %s.\n",
                   dmg, player->name);
            printf("Santé du joueur: %d/%d\n\n",
                   player->health, player->max_health);
            if (player->health <= 0) {
                printf("Vous êtes mort. Fin de la partie.\n"); exit(0);
            }
        }
        sleep(1);
    }
    if (dragon->health <= 0) {
        printf("Dragon vaincu! Vous avez gagné le jeu!\n\n");
        exit(0);
    }
}

void waves_of_enemies(struct Player* player, struct Goblin* goblin,
                      struct Elf* elf, struct Orc* orc,
                      struct Dragon* dragon) {
    for (int wave = 1; wave <= 5; wave++)
        run_wave(player, goblin, elf, orc, dragon, wave);
    handle_dragon_battle(player, goblin, elf, orc, dragon);
}

// MAIN

int main() {
    srand(time(NULL));

    struct Player player;
    struct Goblin goblin;
    struct Elf elf;
    struct Orc orc;
    struct Dragon dragon;

    init_player(&player);
    init_goblin(&goblin);
    init_elf(&elf);
    init_orc(&orc);
    init_dragon(&dragon);

    interactive_menu(&player, &goblin, &elf, &orc, &dragon);

    return 0;
}


