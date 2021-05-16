#include <stdio.h>
#include <stdlib.h>
typedef struct node node;

typedef struct node { union {
        double value;
        char operator;} contents;
    int type;
    int precedence;
    node *next;
} node;


node* createNode(double, int);
node* createConversionNode(double, int, int, char);