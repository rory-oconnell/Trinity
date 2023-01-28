#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

// NB: this skeleton is here to help you - ignore anything that does not help you
// There are a lot of others (and better!) ways of doing this

// note this sekeleton uses a global variable. It therefore will only work with
// one hashtable, of the size set. In general global variables should be avoided
// as their global scope makes it very challenging to see where they are updated
// (as it can be anywhere!), and don't work well when several threads/programs
// update them at the same time (concurency), amongst others problems.
// Having said that, they can make coding a bit easier, so that's why we are using
// one here. If you can, try using a hashTable as a variable, passing it as a
// parameter to functions!



#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 59  //best be prime	//original value 99991

int collisions = 0;
int num_terms = 0;

typedef struct Element Element;
struct Element{
    char* person;
	int frequency;	// frequency of the name in the table
};

Element* hashTable[ARRAY_SIZE];

unsigned long hash(char *str) {

        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % ARRAY_SIZE;

}

Element* createNewElement(char* name){
		int tableIndex = hash(name);
		hashTable[tableIndex] = malloc(sizeof(Element));
		hashTable[tableIndex]->person = malloc(sizeof(char)*MAX_STRING_SIZE);
		strcpy(hashTable[tableIndex]->person, name);
    return NULL;
}


// returns the element with name name or NULL if the element is not present
Element* search (char* name){
	int index = hash(name);
	while(hashTable[index] != NULL)
	{
		collisions++;		// Every time search is invoked, a collision is detected.	// search should not be responsible for collision detection
		return hashTable[index];
	}
    return NULL;
}

// search_lite will look for things without incurring collisions
Element* search_lite (char* name){
	int index = hash(name);
	while(hashTable[index] != NULL)
	{
		if (strcmp(hashTable[index]->person, name) != 0){index++;}
		else{return hashTable[index];
}
	}
    return NULL;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert(char* name){
   // TODO
}

//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){

	if (search(name) == NULL)
	{
		int tableIndex = hash(name);
		hashTable[tableIndex] = malloc(sizeof(Element));
		hashTable[tableIndex]->person = malloc(sizeof(char)*MAX_STRING_SIZE);
		strcpy(hashTable[tableIndex]->person, name);
		hashTable[tableIndex]->frequency++;
		num_terms++;
	}
	else		// Collision detected - check to see if the next spot is occupied
	{
				// if it isn't null, we need to check to see if it is the same name

			int index = hash(name);
			while(hashTable[index] != NULL)
				{
					if(strcmp(hashTable[index]->person, name) == 0)
						{
							hashTable[index]->frequency++;
							break;		// had continue here initially, but created an infinite loop that checked if the names were the same and continued incrementing to infinity
						}
					index++;
				}
			if(hashTable[index] == NULL)
				{
					hashTable[index] = malloc(sizeof(Element));
					hashTable[index]->person = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->person, name);
					hashTable[index]->frequency++;
					num_terms++;
				}


	}

	// if the person doesn't exist, add them at the index, if the person exists, it is a collision and has to be addressed
    // int tableIndex = hash(name);
	// hashTable[tableIndex] = malloc(sizeof(Element));
	// hashTable[tableIndex]->person = malloc(sizeof(char)*MAX_STRING_SIZE);
	// strcpy(hashTable[tableIndex]->person, name);

}


// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences(char* name){
    int count=0;
		Element* person = search_lite(name);
		if(person != NULL)
		{
			count = person->frequency;
			printf(">>> %s - %i \n", name, count);
		}
		else{printf(">>> %s - %i \n", name, count);}
}
// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) && buf[i] != 32){{break;}} // only load letters and numbers
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) {
		printf("Unable to open %s\n", fname);
		return 0;
	}

	// read until the end of the file
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement( buf);                           //here you call your function from above!
	}

	// always remember to close your file stream
	fclose(f);

	return 1;
}

int main()
{
	Element userInput;
	userInput.person = malloc(sizeof(char)*MAX_STRING_SIZE);
	int load_return = load_file("names.csv");
	if(load_return == 1){printf("names.csv loaded!\n");}
	printf("Capacity: %d\n", ARRAY_SIZE);
	printf("Num Terms: %d\n", num_terms);
	printf("Collisions: %d\n", collisions);
	float load = ((float)num_terms / (float)ARRAY_SIZE);
	printf("Load: %f\n", load);
	printf("Enter term to get frequency or type \"quit\" to escape\n");
	//scanf("%s", userInput.person);
	//fgets(userInput.person, MAX_STRING_SIZE, stdin);	// got this from https://www.educative.io/answers/how-to-use-the-fgets-function-in-c
	while(strcmp(userInput.person, "quit") != 0)
		{
			fgets(userInput.person, MAX_STRING_SIZE, stdin);	// this didn't work because it scanf terminates at a space
			userInput.person[strlen(userInput.person)-1]='\0';	// got this from https://stackoverflow.com/questions/51310985/remove-newline-from-fgets-input
																// limits the whitespace read in by fgets
			printNumberOfOccurences(userInput.person);
		}



    //first test insert and search
    //then move on to addOrIncrement
    //only then worry about loading the file
    //and later again about an interactive interface

    return 0;
}