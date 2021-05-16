#include "node.h"

node* createNode(double value, int type) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if(newNode){
        newNode -> contents.value = value;
        newNode -> type = type;
        newNode -> next = NULL;
    } else {
        puts ("Unable to allocate memory.\n");
        return NULL;
    }
    return newNode;
}

node* createConversionNode(double value, int type, int precedence, char operator) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if(newNode){
        if (type == 0){
            newNode -> contents.operator = operator;
        } else {
            newNode->contents.value = value;
        }
        newNode -> precedence = precedence;
        newNode -> type = type;
        newNode -> next = NULL;
    } else {
        puts ("Unable to allocate memory.\n");
        return NULL;
    }
    return newNode;
}