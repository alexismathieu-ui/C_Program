#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "Structfile.h"
//===========================FUNCTION PROTOTYPES==============================//
void stack_init(Stack *s, int capacity);
int stack_is_empty(const Stack *s);
int stack_is_full(const Stack *s);
int stack_push(Stack *s, int value);
int stack_pop(Stack *s, int *out);
void stack_free(Stack *s);
void initNode(Node** head, int count);
void invertList(Node** head);
//===========================================================================//

//=============================FUNCTIONS STACK================================//

void stack_init(Stack *s, int capacity) {
    if (capacity <= 0) {
        s->data = NULL;
        s->capacity = 0;
        s->top = -1;
        return;
    }
    s->data = (int*)malloc(sizeof(int) * capacity);
    if (!s->data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    s->capacity = capacity;
    s->top = -1;
}

int stack_is_empty(const Stack *s) {
    return s->top == -1;
}

int stack_is_full(const Stack *s) {
    return s->top == s->capacity - 1;
}

/* push: retourne 0 si succès, -1 si plein */
int stack_push(Stack *s, int value) {
    if (stack_is_full(s)) return -1;
    s->data[++s->top] = value;
    return 0;
}

/* pop: retourne 0 si succès et écrit la valeur dans out, -1 si vide */
int stack_pop(Stack *s, int *out) {
    if (stack_is_empty(s)) return -1;
    *out = s->data[s->top--];
    return 0;
}

void stack_free(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->capacity = 0;
    s->top = -1;
}

//===========================================================================//

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



int main(){

}