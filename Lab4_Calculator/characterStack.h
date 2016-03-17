#define STACK_MAX 100

struct CharStack
{
    int data[STACK_MAX];
    int size;
};

struct CharStack *newCharStack()
{
    struct CharStack *newStack;
    newStack = malloc( sizeof (struct Stack) );
    newStack -> size = 0;
    return newStack;
}

int pushChar(struct CharStack *stack, char value)
{
    // Only add to stack if
    if( (stack -> size) < STACK_MAX){
        stack -> data[stack -> size] = value;
        stack -> size++;
        
        // Return 1 to signify operation successful
        return 1;
    }else{
        printf("%s\n", "Error: Stack is full");
        // Return 0 to signify full stack
        return 0;
    }  
}

char popChar(struct CharStack *stack)
{
    if (stack -> size == 0){
        printf("%s\n", "Error: Stack is empty, can't pop");
        return '0';
    }else{
        stack -> size--;
        return stack -> data[stack -> size];
    }
}

char isEmpty(struct CharStack *stack)
{
    if (stack -> size == 0){
        // Stack is empty, return 0 char
        return '0';
    }else{
        char value = stack -> data[stack -> size - 1];
        return value;
    }
}