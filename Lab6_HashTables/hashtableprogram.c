#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main(int argc, char * argv[])
{
    struct hash_table * table;
    table = new_hash_table(argc);

    if (argc >= 2) {
        for (int  i = 1; i < argc; i++){
            char *temp = argv[i];
            
            if(strcmp(temp, "+") == 0){
                i++;
                insert(table, argv[i]);
                printf("Inserted: %s\n", argv[i]);
                
            }else if(strcmp(temp, "-") == 0){
                i++;
                remove_item(table, argv[i]);
                printf("Removed: %s\n", argv[i]);
            }else if(strcmp(temp, "=") == 0){
                printf("Printing table%s\n", "");
                print(table);
            }
        }     
    }else{
        printf("%s\n", "No command line arguments entered.");
    }
    
    free_hash_table(table);
    printf("%s\n", "Memory freed.");
    
    return 0;
}