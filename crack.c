#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

//alphabetic()
int alphabetic(const void *a, const void *b){
    return strcmp(*(char **)a, *(char **)b);
}
//strsearch()
int strsearch(const void *key, const void *elem){
    return strcmp((char *)key, *(char **)elem);
}
//append()
void append(char *dest, char *src, char *txt){
    strcpy(dest, src);
    strcat(dest, txt);
}
//capitalize()
void capitalize(char*dest, char *src){
    strcpy(dest, src);
    dest[0] = toupper(dest[0]);
    for (int i=1; i < strlen(dest); i++){
        dest[i] = tolower(dest[i]);
    }
}
//allcapitalize()
void allcapitalize(char*dest, char *src){
    strcpy(dest, src);
    for (int i=0; i < strlen(dest); i++){
        dest[i] = toupper(dest[i]);
    }
}
//capandnum()
void capandnum(char *dest, char *src, char *txt){
    char temp[40];
    append(temp, src, txt);
    allcapitalize(dest, temp);
}



//Main Function
int main(int argc, char *argv[]) { 

    //check if correct amount of args
    if (argc < 3) {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    int size;
    int amt = 0;
    //read a list of ready to crack hashes into an array
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the array of array consisting of hashes using qsort.
    qsort(hashes, size, sizeof(char*), alphabetic);
    /* testing
    for(int i=0; i<size; i++){
        printf("sorted %d: %s\n", i, hashes[i]);
    }
    */
    
    // Open the list of possible passwords file for reading.
    FILE *pass_file = fopen(argv[2], "r");


    //for each possible password,
    char curr_hash[HASH_LEN];
    while(fgets(curr_hash, HASH_LEN, pass_file) != NULL){

        //remove newline
        for(int i=0; i<strlen(curr_hash); i++){
            if(curr_hash[i] == '\n') curr_hash[i] = '\0';
        }

        //hash the possible password
        char *hash = md5(curr_hash, strlen(curr_hash));


        //if found (using linear or binary search)
        // REQUIREMENT: linear search //char *found_hash = linearSearch(hash, hashes, size);
        // CHALLENGE1: Use binary search instead of linear search. (checking if the hashed possible password matches one of the 'leaked' hashes)
        char **found_hash = bsearch(hash, hashes, size, sizeof(char*), strsearch);
        if(found_hash){
            //display the password and hash
            printf("%s %s\n", *found_hash, curr_hash);
            //keep track of amt
            amt++;
        }


        //VARIANTS:
        
        // 1) append 0-9
        for(int i=0; i<10; i++){
            char varient_hash[HASH_LEN] = "";
            char digit[2];
            sprintf(digit, "%d", i);
            append(varient_hash, curr_hash, digit);

            //hash the possible varient password
            char *hash = md5(varient_hash, strlen(varient_hash));
            //check if varient is found
            char **found_hash = bsearch(hash, hashes, size, sizeof(char*), strsearch);
            if(found_hash){
            //display the password and hash
            printf("%s %s\n", *found_hash, varient_hash);
            //keep track of amt
            amt++;
            }
            
        }

        // 2) append ?
        char q_varient_hash[HASH_LEN] = "";
        append(q_varient_hash, curr_hash, "?");

        //hash the possible varient password
        char *q_hash = md5(q_varient_hash, strlen(q_varient_hash));
        //check if varient is found
        char **q_found_hash = bsearch(q_hash, hashes, size, sizeof(char*), strsearch);
        if(q_found_hash){
        //display the password and hash
        printf("%s %s\n", *q_found_hash, q_varient_hash);
        //keep track of amt
        amt++;
        }

        // 3) append !
        char e_varient_hash[HASH_LEN] = "";
        append(e_varient_hash, curr_hash, "!");

        //hash the possible varient password
        char *e_hash = md5(e_varient_hash, strlen(e_varient_hash));
        //check if varient is found
        char **e_found_hash = bsearch(e_hash, hashes, size, sizeof(char*), strsearch);
        if(e_found_hash){
        //display the password and hash
        printf("%s %s\n", *e_found_hash, e_varient_hash);
        //keep track of amt
        amt++;
        }
        
        
        // 4) capitalize first letter
        char v_varient_hash[HASH_LEN] = "";
        capitalize(v_varient_hash, curr_hash);
        //hash the possible varient password
        char *v_hash = md5(v_varient_hash, strlen(v_varient_hash));
        //check if varient is found
        char **v_found_hash = bsearch(v_hash, hashes, size, sizeof(char*), strsearch);
        if(v_found_hash){
        //display the password and hash
        printf("%s %s\n", *v_found_hash, v_varient_hash);
        //keep track of amt
        amt++;
        }

        // 5) capitalize everything
        char c_varient_hash[HASH_LEN] = "";
        allcapitalize(c_varient_hash, curr_hash);
        //hash the possible varient password
        char *c_hash = md5(c_varient_hash, strlen(c_varient_hash));
        //check if varient is found
        char **c_found_hash = bsearch(c_hash, hashes, size, sizeof(char*), strsearch);
        if(c_found_hash){
        //display the password and hash
        printf("%s %s\n", *c_found_hash, c_varient_hash);
        //keep track of amt
        amt++;
        }
        
        /*
        // 6) capitalize everything and append a number
        for(int i=0; i<10; i++){
            char cn_varient_hash[HASH_LEN] = "";
            char digit[2];
            sprintf(digit, "%d", i);
            capandnum(cn_varient_hash, curr_hash, digit);

            //hash the possible varient password
            char *cn_hash = md5(cn_varient_hash, strlen(cn_varient_hash));
            //check if varient is found
            char **cn_found_hash = bsearch(cn_hash, hashes, size, sizeof(char*), strsearch);
            if(cn_found_hash){
            //display the password and hash
            printf("%s %s\n", *cn_found_hash, cn_varient_hash);
            //keep track of amt
            amt++;
            }
        }
        */

        


    }
    

    // TODO
    // When done with the file:
    //   Close the file
    fclose(pass_file);
    //   Display the number of hashes found.
    printf("%d found\n", amt);
    //   Free up memory.
    freeAA(hashes, size);
}
