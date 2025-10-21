#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

typedef struct n{
    int data;
    struct n* next;
} Node;

void initNode(Node** head, int count) {
    if (count <= 0) {
        *head = NULL;
        return;
    }

    Node* cur = NULL; // cur va servir a parcourir la liste
    for (int i = 1; i <= count; ++i) {
        Node* n = (Node*)malloc(sizeof(Node));
        if (!n) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        n->data = i;    // affecte les nombres 1 à count
        n->next = NULL;

        if (cur == NULL) {
            *head = n;
            cur = n;
        } else {
            cur->next = n;
            cur = n;
        }
    }
}

void invertList(Node** head) {
    Node* prev = NULL; // prev = previous
    Node* curr = *head; // curr = current
    Node* next = NULL;
    
    while (curr != NULL) {
        next = curr->next; // sauvegarde le suivant
        curr->next = prev; // inverse le pointeur
        prev = curr;       // avance prev
        curr = next;      // avance curr
    }
    *head = prev; // met à jour la tête de la liste
}


int main() {
    Node* head = NULL;
    
    int value;
    printf("Enter la taille du tableau de votre choix: ");
    scanf("%d", &value);
    
    initNode(&head, value);
    invertList(&head);
    
    Node* cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    return 0;
}