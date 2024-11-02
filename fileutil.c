#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

#define ALLOC_CAPACITY_START 10
#define ALLOC_CAPACITY_INCREMENT 10
#define MAX_LINE_LENGTH 1000


// Return a pointer to an array of strings. (Also sets the value of *size to be the number of valid entries in the array (not the total array length)).
//loadFileAA()
char ** loadFileAA(char *filename, int *size) {

	//inital Array of Array capacity
	int capacity = ALLOC_CAPACITY_START;

	//open file for read
	FILE *file1 = fopen(filename, "r");
	//check for error
	if (!file1) {
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an array of strings (arr).
	char ** arrOfStrings = malloc(ALLOC_CAPACITY_START * sizeof(char *));

	// set size to 0
	*size = 0;

	char currentLine[MAX_LINE_LENGTH];
	// Read the file line by line.
	while(fgets(currentLine, MAX_LINE_LENGTH, file1)){

		// Trim newline.
		char *nl = strchr(currentLine, '\n');
		if(nl) {
			*nl = '\0';
		}

		// Expand array if necessary (realloc).
		if(*size == capacity){
			capacity += ALLOC_CAPACITY_INCREMENT;
			arrOfStrings = realloc(arrOfStrings, capacity * sizeof(char *));
		}

		//   Allocate memory for the string (str).
		char * str = malloc(strlen(currentLine) + 1 * sizeof(char *));
		//   Copy each line into the string (use strcpy).
		strcpy(str, currentLine);
		//   Attach the string to the large array (assignment =).
		arrOfStrings[*size] = str;
		*size = *size + 1;
	}


    // Close the file.
	fclose(file1);
	
	// The size should be the number of entries in the array.
	//*size = count;??
	
	// Return pointer to the array of strings.
	return arrOfStrings;
}


// Search the array for the target string. (returns the string or NULL)
//substringSearchAA()
char * substringSearchAA(char *target, char **lines, int size) {
	for(int i=0; i<size; i++){
		if(strstr(lines[i], target)) return lines[i];
	}
	return NULL;
}


// Free the memory used by the array
//freeAA()
void freeAA(char ** arr, int size){
	for(int i=0; i<size; i++){
		free(arr[i]);
	}
	free(arr);
}

//linearSearch() use strcmp()
char * linearSearch(char *target, char** lines, int size) {
	for(int i=0; i<size; i++){
		if(!strcmp(lines[i], target)) return lines[i];
	}
	return NULL;
}





char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an 2D array, using COLS as the width.
	// Read the file line by line into a buffer.
    //   Trim newline.
	//   Expand array if necessary (realloc).
	//   Copy each line from the buffer into the array (use strcpy).
    // Close the file.
	
	// The size should be the number of entries in the array.
	*size = 0;
	
	// Return pointer to the array.
	return NULL;
}
char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    
    return NULL;
}
void free2D(char (*arr)[COLS]) {
}