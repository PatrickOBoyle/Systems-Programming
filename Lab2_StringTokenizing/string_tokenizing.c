#include <stdio.h>

/*
 * Name: Tokenize
 *
 * Arguments:
 *  1. str[] - character array, containing words and spaces
 *  2. start - start index of the next word to be assigned
 *  3. result[] - char array of the next word
 *
 *  Returns: start index for next word
 *
 * Description:
 *  Uses the character array and starting index provided
 *  to access the next word, assign it to result, and return
 *  the start index of the next word to the caller.
 *
*/
int tokenize(char str[], int start, char result[]){
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

    // Set start index to the beginning of the next word
    while(str[start] == ' '){
        start++;
    }

    return start;
}

int main(){
    const int MAX_STRING = 256;
    char buffer[MAX_STRING];

    fgets(buffer, MAX_STRING, stdin);

    char result[MAX_STRING];

    int start = tokenize(buffer, 0, result);

    // When the end of the input is reached, tokenize will return -1
    while( start != -1){
        printf("%s\n", result);
        start = tokenize(buffer, start, result);
    }

    return 0;
}