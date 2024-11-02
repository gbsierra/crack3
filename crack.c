#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

//Main Function
int main(int argc, char *argv[]) { 
    //check if correct amount of args
    if (argc < 3) {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    int size;
    int amt = 0;
    //read hashes into array
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // Open the password file for reading.
    FILE *pass_file = fopen(argv[2], "r");

    char curr_hash[HASH_LEN];
    //for each password
    while(fgets(curr_hash, HASH_LEN, pass_file) != NULL){
        for(int i=0; i<strlen(curr_hash); i++){
            if(curr_hash[i] == '\n') curr_hash[i] = '\0';
        }
        //hash it
        char *hash = md5(curr_hash, strlen(curr_hash));
        //use the array search (function from fileutil.h)

        //if found
        char *found_hash = linearSearch(hash, hashes, size);
        if(found_hash){
            //display the password and hash
            printf("%s %s\n", found_hash, curr_hash);
            //keep track of amt
            amt++;
        }


    }
    
    // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    fclose(pass_file);
    //   Display the number of hashes found.
    printf("%d found\n", amt);
    //   Free up memory.
    freeAA(hashes, size);
}
