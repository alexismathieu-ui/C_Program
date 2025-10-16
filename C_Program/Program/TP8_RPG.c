#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <math.h>
#include <unistd.h> // Pour la fonction sleep


// STRUCTURES DES PERSONNAGES

struct Player {
    char name[50];
    int health;
    int max_health;
};

struct Dragon {
    int health;
    int max_health;
};

// AFFICHAGE DES PERSONNAGES

void display_player(struct Player* player) {
    printf("Joueur: %s\n", player->name);
    printf("Santé: %d/%d\n", player->health, player->max_health);
}

void display_dragon(struct Dragon* dragon) {
    printf("Santé du Dragon: %d/%d\n", dragon->health, dragon->max_health);
}

// INITIALISATION DES PERSONNAGES

void init_characters(struct Player* player, struct Dragon* dragon) {
    printf("Entrez votre pseudonyme: ");
    scanf("%s", player->name);
    player->max_health = 100;
    player->health = player->max_health;

    dragon->max_health = 100;
    dragon->health = dragon->max_health;
}

// FONCTIONS DE JEU

void roll_dice(int* dice1) {
    *dice1 = rand() % 6 + 1;
}

int roll_dices(int num_dice, int num_faces) {
    int total = 0;
    for (int i = 0; i < num_dice; i++) {
        total += rand() % num_faces + 1;
    }
    return total;
}

void player_attack(struct Player* player, struct Dragon* dragon) {
    int attack_value = roll_dices(3, 6);
    printf("%s attaque avec un jet de %d\n", player->name, attack_value);
    dragon->health -= attack_value;
    if (dragon->health < 0) dragon->health = 0;
}

void dragon_attack(struct Player* player, struct Dragon* dragon) {
    int attack_value = roll_dices(3, 6);
    printf("Le Dragon attaque avec un jet de %d\n", attack_value);
    player->health -= attack_value;
    if (player->health < 0) player->health = 0;
}

//FONCTION DE TOUR DE JEU

void gameTurn(struct Player* player, struct Dragon* dragon) { 
    int player_roll, dragon_roll;
    do {
        roll_dice(&player_roll);
        roll_dice(&dragon_roll);
        printf("%s a lancé un %d\n", player->name, player_roll);
        printf("Le Dragon a lancé un %d\n", dragon_roll);
    } while (player_roll == dragon_roll);

    if (player_roll > dragon_roll) {
        player_attack(player, dragon);
    } else {
        dragon_attack(player, dragon);
    }
}

int main() {
    srand(time(NULL));
    struct Player player;
    struct Dragon dragon;

    init_characters(&player, &dragon);

    while (player.health > 0 && dragon.health > 0) {
        display_player(&player);
        display_dragon(&dragon);
        gameTurn(&player, &dragon);
        printf("\n");
        sleep(1);  // Pause d'une seconde entre chaque tour
    }

    if (player.health <= 0) {
        printf("%s a été vaincu par le Dragon!\n", player.name);
    } else {
        printf("%s a vaincu le Dragon!\n", player.name);
    }

    return 0;
}