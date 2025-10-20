#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

enum Suit { PIQUE, COEUR, CARREAU, TREFLE };
enum Rank { DEUX = 2, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI, AS };

struct Card {
    enum Suit suit;
    int rank;
};

struct Deck {
    int size;
    struct Card cards[52];
};

// Initialise le jeu de 52 cartes
void initialize_deck(struct Deck *deck) {
    deck->size = 52;
    int index = 0;
    for (int suit = PIQUE; suit <= TREFLE; suit++) {
        for (int rank = DEUX; rank <= AS; rank++) {
            deck->cards[index].suit = (enum Suit)suit;
            deck->cards[index].rank = rank;
            index++;
        }
    }
}

// Mélange le deck
void shuffle_deck(struct Deck *deck) {
    srand((unsigned) time(NULL));
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Card tmp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = tmp;
    }
}

// Compare deux cartes
int compare_cards(struct Card card1, struct Card card2) {
    if (card1.rank > card2.rank)
        return 0;
    else if (card1.rank < card2.rank)
        return 1;

    // Même rang → départager par couleur
    if (card1.suit < card2.suit)
        return 0;  // première carte supérieure (Pique plus fort)
    else
        return 1;  // sinon deuxième supérieure
}

// Affiche une carte
void print_card_verbose(struct Card c) {
    const char *suit;
    switch (c.suit) {
        case PIQUE: suit = "Pique"; break;
        case COEUR: suit = "Coeur"; break;
        case CARREAU: suit = "Carreau"; break;
        case TREFLE: suit = "Trefle"; break;
        default: suit = "?"; break;
    }

    const char *rank_str;
    switch (c.rank) {
        case VALET: rank_str = "Valet"; break;
        case DAME:  rank_str = "Dame"; break;
        case ROI:   rank_str = "Roi"; break;
        case AS:    rank_str = "As"; break;
        default: {
            static char buf[3];
            snprintf(buf, sizeof(buf), "%d", c.rank);
            rank_str = buf;
        }
    }

    printf("%s de %s", rank_str, suit);
}

// Coupe le deck mélangé en deux pour créer les paquets des joueurs
void decks_deck_init(struct Deck *deck, struct Deck *player1_deck, struct Deck *player2_deck) {
    player1_deck->size = deck->size / 2;
    player2_deck->size = deck->size / 2;

    for (int i = 0; i < player1_deck->size; i++) {
        player1_deck->cards[i] = deck->cards[i * 2];
        player2_deck->cards[i] = deck->cards[i * 2 + 1];
    }
}

// Jeux d'un tour de bataille
void Playturn(struct Deck *p1, struct Deck *p2) {
    if (p1->size == 0 || p2->size == 0)
        return;

    struct Card pile[52];
    int pile_size = 0;

    int bataille = 1;
    while (bataille) {
        if (p1->size == 0 || p2->size == 0) return;

        // Chaque joueur joue la première carte
        struct Card c1 = p1->cards[0];
        struct Card c2 = p2->cards[0];

        // Retirer la carte du haut
        for (int i = 1; i < p1->size; i++) p1->cards[i - 1] = p1->cards[i];
        for (int i = 1; i < p2->size; i++) p2->cards[i - 1] = p2->cards[i];
        p1->size--;
        p2->size--;

        // Ajouter les cartes au tas central
        pile[pile_size++] = c1;
        pile[pile_size++] = c2;

        printf("\nJoueur 1 joue : ");
        print_card_verbose(c1);
        printf("\nJoueur 2 joue : ");
        print_card_verbose(c2);
        printf("\n");

        int result = compare_cards(c1, c2);

        if (result == 0) {
    printf("→ Joueur 1 gagne le pli !\n");

    for (int i = 0; i < pile_size; i++) {
        int j = rand() % pile_size;
        struct Card tmp = pile[i];
        pile[i] = pile[j];
        pile[j] = tmp;
    }

    for (int i = 0; i < pile_size; i++)
        p1->cards[p1->size++] = pile[i];

    bataille = 0;

} 
else if (result == 1) {
    printf("→ Joueur 2 gagne le pli !\n");

    for (int i = 0; i < pile_size; i++) {
        int j = rand() % pile_size;
        struct Card tmp = pile[i];
        pile[i] = pile[j];
        pile[j] = tmp;
    }

    for (int i = 0; i < pile_size; i++)
        p2->cards[p2->size++] = pile[i];

    bataille = 0;
}
        
    else {
        printf(" ÉGALITÉ ! C’est la BATAILLE ! \n");

        // Chaque joueur met une carte face cachée si possible
        if (p1->size > 0 && p2->size > 0) {
            pile[pile_size++] = p1->cards[0];
            pile[pile_size++] = p2->cards[0];

            for (int i = 1; i < p1->size; i++) p1->cards[i - 1] = p1->cards[i];
            for (int i = 1; i < p2->size; i++) p2->cards[i - 1] = p2->cards[i];
            p1->size--;
            p2->size--;
        } 
            
        else {
            printf("Un joueur n’a plus de cartes pour continuer la bataille.\n");
            bataille = 0;
            }
        }
    
        printf("Taille des paquets : J1 = %d cartes, J2 = %d cartes\n", p1->size, p2->size);
    }
}


int main(void) {
    struct Deck deck;
    struct Deck player1_deck, player2_deck;

    initialize_deck(&deck);
    shuffle_deck(&deck);
    decks_deck_init(&deck, &player1_deck, &player2_deck);

    int round = 1;
    const int max_rounds = 1000;
    while (player1_deck.size > 0 && player2_deck.size > 0 && round <= max_rounds) {
        printf("===== Tour %d =====\n", round++);
        Playturn(&player1_deck, &player2_deck);
    }

    printf("===== Résultat final =====\n");
    if (player1_deck.size > player2_deck.size)
        printf("Joueur 1 gagne la partie avec %d cartes restantes !\n", player1_deck.size);
    else if (player2_deck.size > player1_deck.size)
        printf("Joueur 2 gagne la partie avec %d cartes restantes !\n", player2_deck.size);
    else if (player1_deck.size == player2_deck.size)
        printf("Match nul, les joueurs ont le même nombre de carte\n");
    else
        printf("Match nul, les deux joueurs n'ont plus de cartes\n");

    return 0;
}
