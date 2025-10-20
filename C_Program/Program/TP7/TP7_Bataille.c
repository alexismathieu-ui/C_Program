#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

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

void deal_cards(struct Deck *deck, struct Card *player1_card, struct Card *player2_card) {
    if (deck->size < 2) {
        printf("Pas assez de cartes dans le deck pour distribuer.\n");
        return;
    }
    *player1_card = deck->cards[0];
    *player2_card = deck->cards[1];
    for (int i = 2; i < deck->size; i++) {
        deck->cards[i - 2] = deck->cards[i];
    }
    deck->size -= 2;
}
void print_card_verbose(struct Card c) {
    const char *suit;
    switch (c.suit) {
        case PIQUE: suit = "Pique"; break;
        case COEUR: suit = "Coeur"; break;
        case CARREAU: suit = "Carreau"; break;
        case TREFLE: suit = "Trefle"; break;
        default: suit = "Inconnu"; break;
    }
    printf("%d de %s", c.rank, suit);
}
void decks_deck_init(struct Deck *deck, struct Deck *player1_deck, struct Deck *player2_deck) {
    player1_deck->size = deck->size / 2;
    player2_deck->size = deck->size / 2;
    for (int i = 0; i < player1_deck->size; i++) {
        player1_deck->cards[i] = deck->cards[i * 2];
        player2_deck->cards[i] = deck->cards[i * 2 + 1];
    }
}

void shuffle_deck(struct Deck *deck) {
    srand((unsigned) time(NULL));
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Card tmp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = tmp;
    }
}

// function compare two cards
int compare_cards(struct Card card1, struct Card card2) {
    if (card1.rank > card2.rank)
        return 0;
    else if (card1.rank < card2.rank)
        return 1;  
    
        if (card1.suit < card2.suit)
            return 1;
        else
            return 0;
}
// function deal one card to each player
void deal_cards(struct Deck *deck, struct Card *player1_card, struct 
                                                        Card *player2_card) {
    
    if (deck->size < 2) {
        printf("Pas assez de cartes dans le deck pour distribuer.\n");
        return;
    }
    *player1_card = deck->cards[0];
    *player2_card = deck->cards[1];
    for (int i = 2; i < deck->size; i++) {
        deck->cards[i - 2] = deck->cards[i];
    }
    deck->size -= 2;
}

void decks_deck_init(struct Deck *deck, struct Deck *player1_deck, 
                                        struct Deck *player2_deck) {
    player1_deck->size = deck->size / 2;
    player2_deck->size = deck->size / 2;
    for (int i = 0; i < player1_deck->size; i++) {
        player1_deck->cards[i] = deck->cards[i * 2];
        player2_deck->cards[i] = deck->cards[i * 2 + 1];
    }
} 

//Function that play the card game turn
void Playturn(struct Deck *player1_deck, struct Deck *player2_deck) {
    if (player1_deck->size == 0 || player2_deck->size == 0) {
        printf("Un des joueurs n'a plus de cartes.\n");
        return;
    }

    struct Card card1 = player1_deck->cards[0];
    struct Card card2 = player2_deck->cards[0];

    for (int i = 1; i < player1_deck->size; i++)
        player1_deck->cards[i - 1] = player1_deck->cards[i];
    for (int i = 1; i < player2_deck->size; i++)
        player2_deck->cards[i - 1] = player2_deck->cards[i];

    player1_deck->size--;
    player2_deck->size--;


    printf("Joueur 1 joue : ");
    print_card_verbose(card1);
    printf("\nJoueur 2 joue : ");
    print_card_verbose(card2);
    printf("\n");


    int result = compare_cards(card1, card2);

    if (result == 0) {
 
        player1_deck->cards[player1_deck->size++] = card1;
        player1_deck->cards[player1_deck->size++] = card2;
        printf("Joueur 1 gagne le tour et récupère les cartes.\n");
    } else {

        player2_deck->cards[player2_deck->size++] = card1;
        player2_deck->cards[player2_deck->size++] = card2;
        printf("Joueur 2 gagne le tour et récupère les cartes.\n");
    }

    printf("Taille des paquets : J1 = %d cartes, J2 = %d cartes\n",
           player1_deck->size, player2_deck->size);
}

int main(void) {
    struct Deck deck;
    struct Deck player1_deck, player2_deck;
    int player1_score = 0;
    int player2_score = 0;

    initialize_deck(&deck);
    shuffle_deck(&deck);
    decks_deck_init(&deck, &player1_deck, &player2_deck);

    int rounds = (player1_deck.size < player2_deck.size) ? player1_deck.size : player2_deck.size;

    for (int i = 0; i < rounds; i++) {
        printf("\n--- Tour %d ---\n", i + 1);
        Playturn(&deck, &player1_score, &player2_score);
    }

    printf("\n--- Résultat final ---\n");
    if (player1_score > player2_score) {
        printf("Joueur 1 gagne la partie avec un score de %d contre %d !\n", player1_score, player2_score);
    } else if (player2_score > player1_score) {
        printf("Joueur 2 gagne la partie avec un score de %d contre %d !\n", player2_score, player1_score);
    } else {
        printf("La partie se termine par une égalité avec un score de %d partout !\n", player1_score);
    }

    return 0;
}