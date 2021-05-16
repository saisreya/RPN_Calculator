#include "stack.h"
#include <string.h>
#include <stdbool.h>
double evaluate (char*, int*);
int check_token( char*);
double power(double, double);
char* conversion(char*);
bool associative(char);
int precedence(char);