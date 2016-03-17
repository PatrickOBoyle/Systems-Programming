#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffencode.h"

int main(int argc, char ** argv){
    unsigned char c;
    struct File * file;

    int n_freqs = 256;
    int * freqs = malloc(sizeof(int) * n_freqs);
    
    for(int i = 0; i < n_freqs; i++){
        freqs[i] = 0;
    }
 
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: huffman <filename>\n");
        exit(1);        // exit with error code
    }
 
    file = fopen(argv[1], "r");
    assert( file != NULL );
    c = fgetc(file);      // attempt to read a byte
    
    while( !feof(file) ) {
        freqs[c]++;
        c = fgetc(file);
    }
    
    fclose(file);
    
    for(int i = 0; i < n_freqs; i++){
        if(freqs[i] == 0)
        {
            freqs[i] = 1;
        }
    }
    
    struct node * tree = build_huffman_tree(freqs, n_freqs);
    
    print_huffman_values(tree, "", 0);
    return 0;  // exit without error code
}