#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "characterStack.h"


/*
    For this lab, I decided to create a char stack as well as using
    a double stack. I decided to do this to avoid issues around parsing
    the character stack for doubles if I was to use one, while also
    feeling have two stacks within one "stack" would just be wrong.
*/

int tokenize(char str[], int start, char result[])
{
    // Check for string terminator
    if(str[start] == '\0'){
        return -1;
    }

    // Index of the result
    int wordIndex = 0;

    // Add each char of the current word to the result array
    while(str[start] != ' ' && str[start] != '\0'){
        result[wordIndex] = str[start];
        
        // Increment the start index position & result index position
        wordIndex++;
        start++;
    }
    
    // Append string terminator
    result[wordIndex] = '\0';
    
    start++;
    // Set start index to the beginning of the next word
    while(str[start] == ' '){
        start++;
    }

    return start;
}

/*
    Name: orderOfOperations
    Desc: For use with dedciding order of operations.
          Taking in the char you have via tokenizing (have),
          and the one on the stack (found), decided whether
          you should pop the value on the stack or not.
    Params:
        found: Operator from stack, i.e. X
        have:  Operator from tokenizing i.e. +
    Return:
        int: 1 if you need to pop, 0 if you do not.
*/
int orderOfOperations(char found, char have)
{
    char operator = have;
    
    switch(operator)
    {
        case 'X':
            return 0;
            break;
        case '/':
            if(found == 'X' || found == '/'){
                return 1;
            }else{
                return 0;
            }
            break;
        case '+':
            if(found == 'X' || found == '/' || found == '+'){
                return 1;
            }else{
                return 0;
            }
            break;
        case '-':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

/*
    Name: convertToPolish
    Desc: Taking in the userInput, and providing an outputString,
          convert a standard user entered mathematically question
          to polish notation, and return this via outputString.
    Params:
        userInput[]:    Standard mathematically problem, i.e. ( 2 + 2 ) X 5 / 2
        outputString[]: The input in polish notation,    i.e. 2 2 + 5 X 2 /
*/
void convertToPolish(char userInput[], char outputString[])
{
    struct CharStack *operatationsStack;
    operatationsStack = newCharStack();
    
    int outputIndex = 0;
    
    char tokenString[256];
    
    // Tokenize
    int inputIndex = tokenize(userInput, 0, tokenString);
    
    // When the end of the input is reached, tokenize will return -1
    while( inputIndex != -1){
        if( isdigit(tokenString[0]) )
        {
            int i = 0;
            while( isdigit( tokenString[i] ) )
            {
                outputString[outputIndex] = tokenString[i];
                outputIndex++;
                i++;
            }
            outputString[outputIndex] = ' ';
            outputIndex++;
            
        }else if(tokenString[0] == '(')
        {
            pushChar(operatationsStack, '(');
            
        }else if(tokenString[0] == '+' ||
                tokenString[0] == '-' ||
                tokenString[0] == '/' ||
                tokenString[0] == 'X')
        {
            
            while( orderOfOperations( isEmpty(operatationsStack), tokenString[0]) && isEmpty(operatationsStack) != '0')
            {
                char popped = popChar(operatationsStack);
                outputString[outputIndex] = popped;
                outputIndex++;
                outputString[outputIndex] = ' ';
                outputIndex++;
                
            }
            
            pushChar(operatationsStack, tokenString[0]);
            
        }else if(tokenString[0] == ')'){
            while( isEmpty(operatationsStack) != '(' && isEmpty(operatationsStack) != '0')
            {
                // POP OPERATOR + APPEND TO STRING
                char popped = popChar(operatationsStack);
                outputString[outputIndex] = popped;
                outputIndex++;
                outputString[outputIndex] = ' ';
                outputIndex++;
            }
            // Pop left bracket
            popChar(operatationsStack);
        }
        
        inputIndex = tokenize(userInput, inputIndex, tokenString);
    }
    
    while( isEmpty(operatationsStack) != '0')
    {
        char popped = popChar(operatationsStack);
        outputString[outputIndex] = popped;
        outputIndex++;
        outputString[outputIndex] = ' ';
        outputIndex++;
    }
    
    outputString[outputIndex] = '\0';
    free(operatationsStack); 
}


/*
    Name: calcPolish
    Desc: Taking in a Stack and a char, compute the value
          of a provided input. Needs to be ran with a while loop.
    Params:
        myStack:  A stack with doubles
        result[]: result of tokenization of polish notationed char array
*/
void calcPolish(struct Stack *myStack, char result[])
{
    char resultChar = result[0];
    
    if( isdigit( resultChar ))
    {
        double value = strtod(result, NULL);
        
        // Add number to the stack
        push(myStack, value);
                    
    }
    else if( resultChar == '+' ||
             resultChar == '-' ||
             resultChar == '/' ||
             resultChar == 'X')
    {
        // Pop off the last two values
        int secondNum = pop(myStack);
        int firstNum = pop(myStack);
        
        double result = 0.00;
                    
        if( resultChar == '+' )
            result = firstNum + secondNum; 
        else if( resultChar == '-' )    
            result = firstNum - secondNum;  
        else if( resultChar == '/' )    
            result = firstNum / secondNum;  
        else if( resultChar == 'X')
            result = firstNum * secondNum;  
        
        // Push result onto the stack
        push(myStack, result);
    }
}


int main()
{
    struct Stack *myStack;
    myStack = newStack();
    
    printf("%s\n", "Please enter a valid calculation: ( ( X / + - ) are accepted operators )");
    
    const int MAX_STRING = 256;
    char buffer[MAX_STRING];

    fgets(buffer, MAX_STRING, stdin);
    
    char result[MAX_STRING];
    char outputString[MAX_STRING];
    
    convertToPolish(buffer, outputString);
    printf("%s", "Polish Notation: ");
    printf("%s\n", outputString);
    
    int start = tokenize(outputString, 0, result);
    
    // When the end of the input is reached, tokenize will return -1
    while( start != -1){
        calcPolish(myStack, result);
        start = tokenize(outputString, start, result);
    }
    printf("%s", "Result: ");
    isStackEmpty(myStack);
    
    free(myStack);

    return 0;
}