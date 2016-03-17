#define STACK_MAX 100

struct Stack
{
    int data[STACK_MAX];
    int size;
};

struct Stack *newStack()
{
    struct Stack *newStack;
    newStack = malloc( sizeof (struct Stack) );
    newStack -> size = 0;
    return newStack;
}

int push(struct Stack *stack, double value)
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

int pop(struct Stack *stack)
{
    if (stack -> size == 0){
        printf("%s\n", "Error: Stack is empty");
        return -1;
    }else{
        stack -> size--;
        return stack -> data[stack -> size];
    }
}

int isStackEmpty(struct Stack *stack)
{
    if (stack -> size == 0){
        printf("%s\n", "Error: Stack is empty");
        return 0;
    }else{
        double value = stack -> data[stack -> size - 1];
        printf("%lf\n", value);
        return 1;
    }
}