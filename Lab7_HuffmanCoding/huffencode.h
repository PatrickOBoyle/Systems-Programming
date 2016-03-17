struct node
{
    int freq;
    int leaf;
    
    union{
        struct{
            struct node * left;
            struct node * right;
        }compound;
        
        unsigned char c;
    }u;
};

/*
    Name: New Node
    Desc: Construct for the creation of a new node
    Params:
        - Node 1, of type node
        - Node 2, of type node
    Returns:
        - A newly created node
*/
struct node * new_node(struct node * node_1, struct node * node_2){
    struct node * new_node;
    new_node = malloc( sizeof(struct node) );
    
    new_node -> leaf = 0;
    
    new_node -> u.compound.left = node_1;
    new_node -> u.compound.right = node_2;
    
    new_node -> freq = (node_1 -> freq) + (node_2 -> freq);
    return new_node;
}

/*
    Name: Build Huffman Tree
    Desc: Builds the huffman tree
    Params:
        - Frequencies
        - Number of frequencies
    Returns:
        - A node that is the root element of the huffman tree
*/
struct node * build_huffman_tree(int * freqs, int n_freqs)
{
    struct node ** list;
    list = malloc( sizeof(struct node *) * n_freqs );
    
    for(int i = 0; i < n_freqs; i++)
    {
        struct node * p = malloc( sizeof(struct node) );
        p -> freq = freqs[i];
        p -> leaf = 1;
        unsigned char char_of_i = i;
        p -> u.c = char_of_i;
        
        list[i] = p;
    }
    
    int smallest, smallest2, size = n_freqs;
    while(size > 1){
        smallest = find_smallest_freq(list, size);
        struct node * p, * p2, * compound;
        
        p = list[smallest];
        list[smallest] = list[size -1];
        size--;
        
        smallest2 = find_smallest_freq(list, size);
        p2 = list[smallest2];
        
        compound = new_node(p, p2);
        list[smallest2] = compound;
    }      
    
    return list[0];
}

/*
    Name: Find Smallest Frequency
    Desc: Finds the smallest frequency within the list of nodes, returning the index of the result
    Params:
        - List of nodes, of type node
        - Size of the list, of type integer
    Returns:
        - Index of the node within the list
*/
int find_smallest_freq(struct node ** list, int size){
    int minimum = -1;
    int index_of_minimum;
    
    for(int i = 0; i < size; i++)
    {
        struct node * p = list[i];
        if(p != NULL)
        {
            if(minimum == -1)
            {
                minimum = p -> freq;
                index_of_minimum = i;

            }else if(minimum > p -> freq)
            {
                minimum = p -> freq;
                index_of_minimum = i;
            }
        }
    }
    
    return index_of_minimum;
}

/*
    Name: Print Huffman Values
    Desc: Prints the huffman values
    Params:
        - The current node, of type node
        - The prefix that has been built
        - The depth currently at
*/
void print_huffman_values(struct node * current_node, char * prefix, int depth){
    if(!current_node -> leaf)
    {
        char temp_string[ strlen(prefix) + 2 ];
        
        strcpy(temp_string, prefix);
        strcat(temp_string, "0");
        print_huffman_values(current_node -> u.compound.left, temp_string, depth + 1);
        
        strcpy(temp_string, prefix);
        strcat(temp_string, "1");
        print_huffman_values(current_node -> u.compound.right, temp_string, depth + 1);
    }
    else
    {
        printf("%c: ", current_node -> u.c);
        
        for(int i = 0; i < depth; i++)
        {
            printf("%c", prefix[i]);
        }
        
        printf("\n");
    }      
}