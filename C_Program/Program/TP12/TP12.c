#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "Structfile.h"

//===========================FUNCTION PROTOTYPES==============================//
void initNode(Node** head, int count);
void invertList(Node** head);
void queue_init(Queue *q, int capacity);
void queue_push(Queue *q, int value);
int queue_get(Queue *q, int *out);
int is_empty(Queue q);
void stack_init(Stack *s, int capacity);
int stack_is_empty(const Stack *s);
int stack_is_full(const Stack *s);
int stack_push(Stack *s, int value);
int stack_pop(Stack *s, int *out);
void stack_free(Stack *s);
void reverse_string(char *str);
void reverse_words(char *str);
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

//=============================FUNCTIONS ALGO================================//

void reverse_string(char *str) {
    if (!str) return;
    int len = strlen(str);
    if (len <= 1) return;

    Stack s;
    stack_init(&s, len);

    for (int i = 0; i < len; ++i) {
        stack_push(&s, (unsigned char)str[i]);
    }

    for (int i = 0; i < len; ++i) {
        int c;
        if (stack_pop(&s, &c) == 0) {
            str[i] = (char)c;
        } else {
            str[i] = '\0';
        }
    }

    stack_free(&s);
}

static void sq_init(StringQueue *q, int capacity) {
    if (capacity <= 0) capacity = 4;
    q->data = (char**)malloc(sizeof(char*) * capacity);
    if (!q->data) { perror("malloc"); exit(EXIT_FAILURE); }
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
}

static void sq_free(StringQueue *q) {
    free(q->data);
    q->data = NULL;
    q->capacity = 0;
    q->front = 0;
    q->size = 0;
}

static void sq_expand_if_needed(StringQueue *q) {
    if (q->size < q->capacity) return;
    int newcap = q->capacity * 2;
    char **newdata = (char**)malloc(sizeof(char*) * newcap);
    if (!newdata) { perror("malloc"); exit(EXIT_FAILURE); }
    for (int i = 0; i < q->size; ++i) {
        newdata[i] = q->data[(q->front + i) % q->capacity];
    }
    free(q->data);
    q->data = newdata;
    q->capacity = newcap;
    q->front = 0;
}

static void sq_push(StringQueue *q, char *item) {
    sq_expand_if_needed(q);
    int idx = (q->front + q->size) % q->capacity;
    q->data[idx] = item;
    q->size++;
}

static char *sq_get(StringQueue *q) {
    if (q->size == 0) return NULL;
    char *out = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return out;
}

static int enqueue_tokens(StringQueue *q, char *s) {
    const char *delim = " \t\n";
    int count = 0;
    char *token = strtok(s, delim);
    while (token) {
        char *dup = strdup(token);
        if (!dup) { perror("strdup"); exit(EXIT_FAILURE); }
        sq_push(q, dup);
        ++count;
        token = strtok(NULL, delim);
    }
    return count;
}

static char **collect_words(StringQueue *q, int count) {
    char **arr = (char**)malloc(sizeof(char*) * count);
    if (!arr) { perror("malloc"); exit(EXIT_FAILURE); }
    for (int i = 0; i < count; ++i) arr[i] = sq_get(q);
    return arr;
}

static void rebuild_string(char *s, char **words, int count) {
    char *p = s;
    for (int i = count - 1; i >= 0; --i) {
        size_t l = strlen(words[i]);
        memcpy(p, words[i], l);
        p += l;
        if (i > 0) { *p = ' '; ++p; }
        free(words[i]);
    }
    *p = '\0';
    free(words);
}

void reverse_words(char *str) {
    if (!str) return;
    StringQueue q;
    sq_init(&q, 8);
    int count = enqueue_tokens(&q, str);
    if (count == 0) {
        str[0] = '\0';
        sq_free(&q);
        return;
    }
    char **words = collect_words(&q, count);
    rebuild_string(str, words, count);
    sq_free(&q);
}

//===========================================================================//

//=============================FUNCTIONS QUEUE================================//

void queue_init(Queue *q, int capacity) {
    if (capacity <= 0) {
        q->data = NULL;
        q->capacity = 0;
        q->front = 0;
        q->rear = -1;
        return;
    }
    q->data = (int*)malloc(sizeof(int) * capacity);
    if (!q->data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
}

void queue_push(Queue *q, int value) {
    if ((q->rear + 1) % q->capacity == q->front) {
        perror("Queue full");
        exit(EXIT_FAILURE);
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
}

int queue_get(Queue *q, int *out) {
    if (!q || q->capacity == 0) return -1;
    if (q->front == (q->rear + 1) % q->capacity) {
        return -1;
    }
    *out = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    return 0;
}

int is_empty(Queue q) {
    if (q.capacity == 0) return 0; // consider empty if no capacity
    return (q.front == ((q.rear + 1) % q.capacity)) ? 0 : 1;
}

//============================================================================//

//=============================FUNCTIONS STACKS===============================//

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

//============================================================================//


int main(){
    char buf[1000];

    printf("Entrer une phrase pour inverser les caractères: ");
    if (scanf(" %999[^\n]", buf) == 1) {
        reverse_string(buf);
        printf("Chaîne inversée: %s\n", buf);
    }

    printf("Entrer une phrase pour inverser ses mots: ");
    if (scanf(" %999[^\n]", buf) == 1) {
        reverse_words(buf);
        printf("Mots inversés: %s\n", buf);
    }

    return 0;
}