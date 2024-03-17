//  CS2130 HW9 Postfix Calculator.
//  Zhiyuan Chang vgs3qt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    // Use an array to store the inputs.
    int count;
    int store[1000000];
} Stack;

void printStack(Stack *s) {
    // Printing the Stack. 
    char before = '[';
    for (int i = 0; i <= s->count; ++i) {
        // Print them in order, one by one. 
        // Stop at count value so we will not print what is used in calculation.
        printf("%c %d", before, s->store[i]);
        before = ',';
    }
    // End with the ].
    puts(" ]");
}

void initialize(Stack *first) {
    // Make the count as -1 for the first value. 
    first->count = -1;
}

void push(Stack *s, int value) {
    // Add a new value into stack, so item[count+1] stores the new value.
    s->store[++s->count] = value;
}


int pop(Stack *s) {
    // When we remove, we return the value and decrease count by 1.
    return s->store[s->count--];
}


int main() {
    Stack stack;
    initialize(&stack);
    // Make the size larger for gargantuan stack.
    char input[1000000];

    while (fgets(input, 1000000, stdin)) {
        // Split the input into tokens. Split by space and blank line.
        char *token = strtok(input, " \n");
        // Stop when token == NULL.
        while (token != NULL) {
            // Check if it is digit, positive and negative.
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))  {
                push(&stack, atoi(token));
            } 
            // Check if the input is an operator.
            else if (strlen(token) == 1 && strchr("+-*%", token[0])){
                // Exit and print the stack if there is only one number left.
                if (stack.count < 1) {
                    printStack(&stack);
                    return 1;
                }
                // Do the calculation. 
                int operandnew = pop(&stack);
                int operandold = pop(&stack);
                switch (token[0]) {
                    case '+':
                        push(&stack, operandold + operandnew);
                        break;
                    case '-':
                        push(&stack, operandold - operandnew);
                        break;
                    case '*':
                        push(&stack, operandold * operandnew);
                        break;
                    case '%':
                        push(&stack, operandold % operandnew);
                        break;
                }
            }
            else{
                // If we input an invalid literals. Print stack and exit.
                printStack(&stack);
                return 1;
            }
            // After each input, we pause the while loop.
            token = strtok(NULL, " \t\n");
        }
    }
    // Print the stack.
    printStack(&stack);
    return 0;
}
