#include "stack.h"
node *HEAD = NULL;

void push(node* node){
    if (!HEAD){
        HEAD=node;
    } else {
        node->next = HEAD;
        HEAD = node;
    }
}
node* pop(){
    struct node *walker = NULL;
    if (!HEAD){
        return NULL;
    } else {
        walker = HEAD;
        HEAD = walker -> next;
        return walker;
    }
}

node* peek(){
    if (!HEAD){
        return NULL;
    } else {
        return HEAD;
    }
}

void clearStack(){
    struct node *walker = NULL;
    struct node *upstream = NULL;
    walker = HEAD;
    while (walker) {
        upstream = walker;
        free(upstream);
        walker = walker->next;
    }
}