#include "rpn.h"
#include "errors.h"

double evaluate (char* expression, int* status){
    if (expression == NULL){
        *status= NULL_EXPRESSION;
        return 0;
    }
    char* end;
    double number;
    node* newNode = NULL;
    node* returnNode = NULL;
    char* token = strtok(expression, " ");
    if(check_token(token) == 1){
        number = strtod(token,&end);
        newNode = createNode(number, 1);
        push(newNode);
    } else {
         *status=FIRST_TOKEN_ERROR;
         return 0;
    }
    token=strtok(NULL, " ");
    while(token){
        if(check_token(token) == 1){
            number = strtod(token,&end);
            newNode = createNode(number, 1);
            push(newNode);
        } else if(check_token(token) == 0) {
            node* num1 = pop();
            node* num2 = pop();
            if (num1 == NULL || num2 == NULL){
                *status=OPERATOR_ERROR;
                return 0;
            }
            switch (token[0]) {
                case '+': returnNode = createNode((num1->contents.value)+(num2->contents.value), 1);
                    push(returnNode);
                    break;
                case '-': returnNode = createNode((num2->contents.value)-(num1->contents.value), 1);
                    push(returnNode);
                    break;
                case '*': returnNode = createNode((num1->contents.value)*(num2->contents.value), 1);
                    push(returnNode);
                    break;
                case '/': if(num1->contents.value==0){*status=6;return 0;}
                    returnNode = createNode((num2->contents.value)/(num1->contents.value), 1);
                    push(returnNode);
                    break;
                case '^': returnNode = createNode((power(num2->contents.value, num1->contents.value)), 1);
                    push(returnNode);
                    break;
                default:
                    *status=INVALID_OPERATOR;
                    return 0;
            }
        } else {
            *status=INVALID_TOKEN;
            return 0;
        }
        token=strtok(NULL, " ");
    }
    node* finalResult = pop();
    if(HEAD != NULL){
        *status=OPERAND_ERROR;
        return 0;
    }
    return finalResult->contents.value;
}


int check_token(char* number_arg){
    char* number=number_arg;
    int flag = 0;
    int returnValue = 1;
    for( ; *number; number++ ){
        if( (*number >= '0' && *number <= '9') || *number == '.'){
            if(*number=='.'){
                if(flag == 0){
                    flag = 1;
                }else{
                    returnValue = -1;
                    break;
                }
            }
        }else{
            returnValue = -1;
            break;
        }
    }
    number=number_arg;
    if(returnValue == -1){
        if(*number == '+' || *number == '-' || *number == '*' || *number == '/' || *number == '^'){
            if(*(number+1) == 0){
                returnValue = 0;
            }
        }
    }
    number=number_arg;
    if (returnValue == -1){
        if (*number == '(' || *number == ')'){
            returnValue=10;
        }
    }

    return returnValue;
}

double power(double base, double number) {
    if (number != 0)
        return (base * power(base, number - 1));
    else
        return 1;
}

int precedence(char operator){
    switch (operator) {
        case '+':return 0;
        case '-':return 0;
        case '*':return 1;
        case '/':return 1;
        case '^':return 2;
    }
}

bool associative(char operator){
    switch (operator) {
        case '+':return false;
        case '-':return true;
        case '*':return false;
        case '/':return true;
        case '^':return true;
    }
}

char* conversion(char* infix){
    if (infix == NULL || *infix == ' '){
        return NULL;
    }
    char* array = calloc(200, sizeof(int));
    char* intArray = calloc(200, sizeof(int));
    int copy=0;
    while(infix[copy]!=0){
        intArray[copy]=infix[copy];
        copy++;
    }
    intArray[copy-1]=0;
    int arrayPoint=0;
    node* newNode = NULL;
    char* token = strtok(intArray, " ");
    if(token && check_token(token)==-1){
        return NULL;
    }
    if(check_token(token) == 1){
        int tokenPoint = 0;
        while(token[tokenPoint]){
            array[arrayPoint] = token[tokenPoint];
            tokenPoint++;
            arrayPoint++;
        }
        array[arrayPoint]=' ';
        arrayPoint++;
    } else if(*token == '('){
            newNode = createConversionNode(0, 0, precedence(*token), *token);
            push(newNode);
    }
    else{
        return 0;
    }

    token=strtok(NULL, " ");
    if(token && check_token(token)==-1){
        return NULL;
    }
    while (token){
        if(check_token(token) == 1){
            int tokenPoint = 0;
            while(token[tokenPoint]){
                array[arrayPoint] = token[tokenPoint];
                tokenPoint++;
                arrayPoint++;
            }
            array[arrayPoint]=' ';
            arrayPoint++;
        }
        else if(check_token(token) == 0){
            while(HEAD &&
            ((peek()->precedence > precedence(*token)) ||
            (peek()->precedence == precedence(*token) && associative(*token)==true))
            && peek()->contents.operator != '('){
                array[arrayPoint] = pop()->contents.operator;
                arrayPoint++;
                array[arrayPoint]=' ';
                arrayPoint++;
            }
            newNode = createConversionNode(0, 0, precedence(*token), *token);
            push(newNode);
        }
        else if (*token == '('){
            newNode = createConversionNode(0, 0, precedence(*token), *token);
            push(newNode);
        }
        else if (*token == ')'){
            node* tempNode = peek();
            while(tempNode && tempNode->contents.operator != '('){
                array[arrayPoint] = pop()->contents.operator;
                arrayPoint++;
                array[arrayPoint]=' ';
                arrayPoint++;
                tempNode = peek();
            }
            if (peek() && peek()->contents.operator == '('){
                pop();
            } else {
                return NULL;
            }
        }
        token=strtok(NULL, " ");
        if(token && check_token(token)==-1){
            return NULL;
        }
    }
    while(HEAD){
        array[arrayPoint] = pop()->contents.operator;
        arrayPoint++;
        array[arrayPoint]=' ';
        arrayPoint++;
    }
    array[arrayPoint-1]=0;
    return (array);
}
