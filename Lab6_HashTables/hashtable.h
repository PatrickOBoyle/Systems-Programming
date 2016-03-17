struct node
{
    char * data;
    struct node * next;
};

struct hash_table
{
    unsigned int size;
    struct node ** table;
};

struct node * new_node(char * item)
{
    struct node * node_new;
    node_new = malloc( sizeof(struct node) );
    
    node_new -> data = item;
    node_new -> next = NULL;
    
    return node_new;
}

struct hash_table * new_hash_table(int input_size)
{
    if( input_size <= 0)
    {
        return NULL;
    }
    
    struct hash_table * new_table;
    new_table = malloc( sizeof(struct hash_table) );
    new_table -> size = input_size;
    
    //size paramater is number of paramaters +1 for inital call, should change size of talbe?
    new_table -> table = malloc( sizeof(struct node) * input_size );
    
    for(int i = 0; i < input_size; i++){
        new_table -> table[i] = NULL;
    }
    
    return new_table;
}

// Return 1 if string is already in table, 0 otherwise
int lookup(struct hash_table * this, char * item)
{
    unsigned int hash_index = hash_string(item) % this -> size;

    struct node * pointer = this -> table[hash_index];

    while(pointer != NULL)
    {
        if( pointer -> data == item){
            return 1;
        }
        
        pointer = pointer -> next;
    }
    return 0;
}

// Print out each entry in the hash table and the values
// stored at that entry
int print(struct hash_table * this)
{
    for(int i = 0; i < this -> size; i++)
    {
        struct node * pointer = this -> table[i];  
        while(pointer != NULL)
        {
            printf("%s%s", pointer -> data, " ");
            pointer = pointer -> next;
        }
    }
    printf("\n");
}

int hash_string(char * string)
{
    unsigned int hash = 0;
    
    for(int i = 0; string[i] != '\0'; i++)
    {
        hash = hash * 37 + string[i];   
    }
    
    return hash;
}

// Free up memory from the table before deleting it
void free_hash_table(struct hash_table * this)
{
    for(int i = 0; i < this -> size; i++){
        struct node * pointer = this -> table[i];
        struct node * next_pointer;
        
        if(pointer == NULL)
        {
            free(pointer);
        }else
        {
            while(pointer != NULL)
            {
                next_pointer = pointer -> next;
                free(pointer);
                pointer = next_pointer;
            }
        }
    }
}

// Insert item to hash table, if already there, do nothing
void insert(struct hash_table * this, char * item)
{
    if( !lookup(this, item) )
    {
        unsigned int hash_index = hash_string(item) % this -> size;
        struct node * pointer = this -> table[hash_index];
        struct node * to_insert;
        
        to_insert = new_node(item);
        
        if(pointer == NULL)
        {
            this -> table[hash_index] = to_insert;
        } else
        {
            while(pointer -> next  != NULL)
            {
                pointer = pointer -> next;
            }
            
            pointer -> next = to_insert;
        }
    }
}

// Remove string from the hash table, if not there, do nothing
void remove_item(struct hash_table * this, char * item)
{
    if(lookup(this, item)){
        unsigned int hash_index = hash_string(item) % this -> size;
        
        struct node * pointer = this -> table[hash_index];
        struct node * prev_pointer;
        
        if(pointer -> next == NULL)
        {
            this -> table[hash_index] = NULL;
            free(pointer);
        } else
        {
            while(pointer -> next != NULL)
            {
                prev_pointer = pointer;
                pointer = pointer -> next;
                
                if(strcmp(item, pointer -> data) == 0)
                {
                    prev_pointer -> next = pointer -> next;
                    free(pointer);
                }
            }
        }      
    }
}