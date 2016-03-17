struct bitset
{
    unsigned int * bitVector;
    int numIndexes;
};

// create a new, empty bit vector set of 'size' items
struct bitset * bitset_new(int size)
{
    struct bitset *new_bitset;
    new_bitset = malloc( sizeof (struct bitset) );
    
    // 
    new_bitset -> bitVector = malloc(size * sizeof(int) + 1);
    
    // ints are 32bits, so to be safe,
    // size / 32 = number of indexes
    // +1 to cover some edge cases
    int indexes = (size / 32) + 1;
    new_bitset -> numIndexes = indexes;
    
    // Set each int to 0
    for(int i = 0; i < indexes; i++){
        new_bitset -> bitVector[i] = 0;
    }
    
    return new_bitset;
}

// check to see if an item is in the set
// returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
int bitset_lookup(struct bitset * this, int item){
    if(item < 0 || item > this -> numIndexes * 32){
        return -1;
    }else{
        // Find the index, similar to how it was decided earlier
        int index = item / 32;
        // Get the position in the index of the item to be checked
        int bit_to_check = item % 32;
        
        int arrayItem = this -> bitVector[index];
        // Set the bit via ANDing with 1
        return (arrayItem >> bit_to_check) & 1;
    }
}

// add an item, with number 'item' to the set
// (returns 0 if item is out of bounds, 1 otherwise)
// has no effect if the item is already in the set
int bitset_add(struct bitset * this, int item){
    if(item < 0 || item > this -> numIndexes * 32){
        return 0;
    }else if( bitset_lookup(this, item) ){
        // If it's already there, just return 1
        return 1;
    }else{
        // As described in lookup
        int index = item / 32;
        int bit_to_set = item % 32;

        int arrayItem = this -> bitVector[index];
        // Set the bit via ORing
        this -> bitVector[index] = arrayItem |= 1 << bit_to_set;
        return 1;
    }
}

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(struct bitset * this, int item){
    if(item < 0 || item > this -> numIndexes * 32){
        return 0;
    }else{
        // As described in lookup
        int index = item / 32;
        int bit_to_set = item % 32;
        
        int arrayItem = this -> bitVector[index];
        this -> bitVector[index] = arrayItem &= ~(1 << bit_to_set); 
        return 1;
    }
}

// place the union of src1 and src2 into dest
// 
void bitset_union(struct bitset * dest, 
                  struct bitset * src1, 
                  struct bitset * src2){
    
    // Assuming all sets have the same size
    for(int i = 0; i < src1 -> numIndexes; i++){
        // Get the number from each src
        int src1Items = src1 -> bitVector[i];
        int src2Items = src2 -> bitVector[i];
        
        // OR the two numbers, as or will give
        // the union of both sets
        int result = src1Items | src2Items;
        
        // Save the union result
        dest -> bitVector[i] = result;
    }
}

// place the intersection of src1 and src2 into dest
void bitset_intersect(struct bitset * dest,
                      struct bitset * src1,
                      struct bitset * src2){
    
    // Assuming all sets have the same size
    for(int i = 0; i < src1 -> numIndexes; i++){
        // Get the number from each src
        int src1Items = src1 -> bitVector[i];
        int src2Items = src2 -> bitVector[i];
        
        // AND the two numbers, as or will give
        // the intersection of both sets
        int result = src1Items & src2Items;
        
        // Save the intersection result
        dest -> bitVector[i] = result;
    }
}

// Function to print the bits of the set
// to see which have been set
void bitset_print(struct bitset * set){
    int bit = 0;
    
    for(int i = 0; i < set -> numIndexes; i++){
        int number = set -> bitVector[i];
        // prints each bit of the set in a line
        for(int j = 0; j < 32; j++){
            bit = (number >> j) & 1;
            printf("%d", bit);
        }
    }
    printf("%s\n", "");
}