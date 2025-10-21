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
        n->data = i;    // affecte les nombres 1..count
        n->next = NULL;

        if (cur == NULL) {
            *head = n;
            cur = n;
        } 
        else {
            cur->next = n;
            cur = n; 
        }
    }
}

int sumList(Node* head) {
    int sum = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        sum += cur->data;
    }
    return sum;
}


int main() {
    Node* head = NULL;
    
    int value;
    printf("Enter la taille du tableau de votre choix: ");
    scanf("%d", &value);
    
    initNode(&head, value);
    int total = sumList(head);
    printf("La somme de la liste chaînée est : %d\n", total);
    return 0;
}