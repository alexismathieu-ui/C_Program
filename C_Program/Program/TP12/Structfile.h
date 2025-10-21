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

typedef struct {
    int *data;
    int top;       // index of the current top element (-1 when empty)
    int capacity;  // maximum number of elements
} Stack;

typedef struct {
    int *data;
    int front;
    int rear;
    int capacity;
} Queue;

typedef struct {
    char **data;
    int capacity;
    int front;
    int size;
} StringQueue;