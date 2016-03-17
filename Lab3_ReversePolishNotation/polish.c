#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

/*
 * Name: Tokenize
 *
 * Arguments:
 *  1. str[] - character array, containing words and spaces
 *  2. start - start index of the next word to be assigned
 *  3. Stack - a stack to push and pop from
 *
 * Description:
 *  Uses the character array and starting index provided
 *  to access the next item, deal with it via the stack,
 *  and then put the result back on the stack.
 *
*/
void tokenize(char str[], int start, struct Stack *myStack)
{
    // Add each char of the current word to the result array
    while(str[start] != '\0')
    {   
        if( str[start] != ' ')
        {
            if( isdigit( str[start] ))
            {
                double value = 0;
                // Getting numbers which may be larger than a single digit
                while(str[start] != '\0' && str[start] != ' ')
                {
                    value *= 10;
                    value += (double)str[start] - 48;
                    start++;
                }
                
                // Add number to the stack
                push(myStack, value);
                
            }else if( str[start] == '+' ||
                    str[start] == '-' ||
                    str[start] == '/' ||
                    str[start] == 'X')
            {
                // Pop off the last two values
                int secondNum = pop(myStack);
                int firstNum = pop(myStack);

                double result = 0.00;
                
                if( str[start] == '+' )
                    result = firstNum + secondNum; 
                else if( str[start] == '-' )    
                    result = firstNum - secondNum;  
                else if( str[start] == '/' )    
                    result = firstNum / secondNum;  
                else if( str[start] == 'X')
                    result = firstNum * secondNum;  

                // Push result onto the stack
                push(myStack, result);
            }
        }
        // Increment the start index position & result index position
        start++;
    }
    // Display the answer
    printStackTop(myStack);
}


int main()
{
    struct Stack *myStack;
    myStack = newStack();
    
    printf("%s\n", "Please enter a postfix expression:");
    
    const int MAX_STRING = 256;
    char buffer[MAX_STRING];

    fgets(buffer, MAX_STRING, stdin);

    // Tokenize
    tokenize(buffer, 0, myStack);
    
    free(myStack);

    return 0;
}