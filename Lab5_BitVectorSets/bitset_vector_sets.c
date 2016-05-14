#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

// To deal with the extended ASCII Chart
unsigned int MAX_SIZE = 256;

/*
    The program creates 4 sets,
        set1, set2,
        union_result_set,
        intersect_result_set

    Each set has a max size of 256,
    to match the extended ASCII Chart.

    I did some testing similar to unit
    testing below, before I implemented
    a printing function to the ADT.
*/

int main()
{
    char input1[MAX_SIZE];
    char input2[MAX_SIZE];

    printf("%s\n", "Enter the first line of input:");
    fgets(input1, MAX_SIZE, stdin);

    printf("%s\n", "Enter the second line of input:");
    fgets(input2, MAX_SIZE, stdin);

    struct bitset * set1;
    set1 = bitset_new(MAX_SIZE);

    struct bitset * set2;
    set2 = bitset_new(MAX_SIZE);

    // Create bitsets for the result of
    // union & intersection function calls
    struct bitset * union_result_set;
    union_result_set = bitset_new(MAX_SIZE);

    struct bitset * intersect_result_set;
    intersect_result_set = bitset_new(MAX_SIZE);

    // Can't accept the newline bit, but it was being
    // set each time the fgets call was made and being added

    // Add all the input from string to set1
    for(int i = 0; input1[i] != '\0'; i++){
        if(input1[i] != '\n')
            bitset_add(set1, input1[i]);
    }

    // Add all the input from string to set2
    for(int i = 0; input2[i] != '\0'; i++){
        if(input2[i] != '\n')
            bitset_add(set2, input2[i]);
    }

    bitset_union(union_result_set, set1, set2);

    bitset_intersect(intersect_result_set, set1, set2);

    // Some quick testing I did to make sure things worked
    // Required me to manually enter the desired chars

    // Test adding, removal and lookup
//    printf("Lookup for '2' = %d, expected 1\n", bitset_lookup(set1, '2'));
//    printf("Remove for '2' = %d, expected 1\n", bitset_remove(set1, '2'));
//    printf("Lookup for '2' = %d, expected 0\n", bitset_lookup(set1, '2'));
//
//    printf("Lookup for '3' = %d, expected 1\n", bitset_lookup(set1, '3'));
//    printf("Remove for '3' = %d, expected 1\n", bitset_remove(set1, '3'));
//    printf("Lookup for '3' = %d, expected 0\n", bitset_lookup(set1, '3'));

//     Test union
//    printf("Lookup for '1' = %d, expected 1\n", bitset_lookup(union_result_set, '1'));
//    printf("Lookup for '2' = %d, expected 1\n", bitset_lookup(union_result_set, '2'));
//
//     Test intersection
//    printf("Lookup for '1' = %d, expected 1\n", bitset_lookup(intersect_result_set, '1'));
//    printf("Lookup for '2' = %d, expected 1\n", bitset_lookup(intersect_result_set, '2'));
//    printf("Lookup for '3' = %d, expected 0\n", bitset_lookup(intersect_result_set, '3'));

//    printf("%s\n", "Set 1:");
//    bitset_print(set1);
//
//    printf("%s\n", "Set 2:");
//    bitset_print(set2);
    bitset_print(union_result_set);
    bitset_print(intersect_result_set);

    return 0;
}
