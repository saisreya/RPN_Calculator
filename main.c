#include "rpn.h"
int main(int argc, char* argv[]) {
    char dataLine[200];
    FILE *data = fopen(argv[1], "r");
    if (!data) {
        perror("I/O error: ");
        return -1;
    }
    FILE *output = fopen(argv[2],"w");
    if (!output) {
        perror("I/O error: ");
        return -1;
    }
    while (fgets(dataLine, 200, data)) {

        fprintf(output,"Infix: %s", dataLine);
        char* postfix = conversion(dataLine);
        fprintf(output,"Postfix: %s\n", postfix);
        clearStack();
        int status=0;
        double result = evaluate(postfix,&status);
        fprintf(output,"Result: %f\n", result);
        switch (status) {
            case 1:
                fprintf(output,"Null expression caused by an invalid token or extra parenthesis\n");
                break;
            case 2:
                fprintf(output,"First value is invalid\n");
                break;
            case 3:
                fprintf(output,"There were to many operators\n");
                break;
            case 4:
                fprintf(output,"Invalid operator inputted\n");
                break;
            case 5:
                fprintf(output,"Invalid value inputted\n");
                break;
            case 7:
                fprintf(output,"There were too many operands\n");
                break;
            default:
                break;
        }
        fprintf(output,"\n");
    }

    fclose(data);
    fclose(output);
    return 0;
}

