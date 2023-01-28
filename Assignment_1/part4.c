#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 99991  //best be prime//original value 99991

int collisions = 0;
int num_terms = 0;
int newLine = 0;
int catCounter = 0; // used to count categories ... not cats.
int NUM_CATEGORIES = 10;
char holder_Array[MAX_STRING_SIZE];

typedef struct Element Element;
struct Element{
    char* Person_ID;		// 0
    char* Deposition_ID;	// 1
    char* Surname;			// 2
    char* Forename;			// 3
    char* Age;				// 4
    char* Person_Type;		// 5
    char* Gender;			// 6
    char* Nationality;		// 7
    char* Religion;			// 8
    char* Occupation;		// 9
	Element* next;
};

Element holder;
Element* cursor;
Element* previous;
Element* hashTable[ARRAY_SIZE];

unsigned long hash(char *str) {

        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % ARRAY_SIZE;

}


//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
		int tableIndex = hash(name);
		hashTable[tableIndex] = malloc(sizeof(Element));
		hashTable[tableIndex]->Person_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Deposition_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Forename = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Age = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Person_Type = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Gender = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Nationality = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Religion = malloc(sizeof(char)*MAX_STRING_SIZE);
		hashTable[tableIndex]->Occupation = malloc(sizeof(char)*MAX_STRING_SIZE);
}

void next_token ( char *buf, FILE *f, int string_max ) {	// Need something to signal that a new line has been encountered
	// start by skipping any characters we're not interested in
	newLine = 0;
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( buf[i] == 10 || (i > 3 && buf[i] == 34 && catCounter == 9)){{newLine++;}} // only load letters and numbers and spaces
		if( !isalnum(buf[i]) && buf[i] != 32){{break;}} // only load letters and numbers and spaces
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
		if (catCounter == 0){strcpy(holder.Person_ID, buf);}
		if (catCounter == 1){strcpy(holder.Deposition_ID, buf);}
		if (catCounter == 2){strcpy(holder.Surname, buf);}
		if (catCounter == 3){strcpy(holder.Forename, buf);}
		if (catCounter == 4){strcpy(holder.Age, buf);}
		if (catCounter == 5){strcpy(holder.Person_Type, buf);}
		if (catCounter == 6){strcpy(holder.Gender, buf);}
		if (catCounter == 7){strcpy(holder.Nationality, buf);}
		if (catCounter == 8){strcpy(holder.Religion, buf);}
		if (catCounter == 9){strcpy(holder.Occupation, buf);}
		catCounter++;
		if (catCounter > 9){catCounter = 0;}
		if (newLine != 0){
			int index = hash(holder.Surname);
			if (hashTable[index] == NULL){
					hashTable[index] = malloc(sizeof(Element));
					hashTable[index]->Person_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Person_ID, holder.Person_ID);
					hashTable[index]->Deposition_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Deposition_ID, holder.Deposition_ID);
					hashTable[index]->Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Surname, holder.Surname);
					hashTable[index]->Forename = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Forename, holder.Forename);
					hashTable[index]->Age = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Age, holder.Age);
					hashTable[index]->Person_Type = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Person_Type, holder.Person_Type);
					hashTable[index]->Gender = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Gender, holder.Gender);
					hashTable[index]->Nationality = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Nationality, holder.Nationality);
					hashTable[index]->Religion = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Religion, holder.Religion);
					hashTable[index]->Occupation = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Occupation, holder.Occupation);
					hashTable[index]->next = NULL;
					num_terms++;
			}
			else if (hashTable[index] != NULL && strcmp(hashTable[index]->Surname, holder.Surname) == 0){
				//Create a new node that has the pointer from the previous node pointing to it
				struct Element* new_node = (struct Element*) malloc(sizeof(struct Element));
					new_node->Person_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Person_ID, holder.Person_ID);

					new_node->Deposition_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Deposition_ID, holder.Deposition_ID);

					new_node->Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Surname, holder.Surname);

					new_node->Forename = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Forename, holder.Forename);

					new_node->Age = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Age, holder.Age);

					new_node->Person_Type = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Person_Type, holder.Person_Type);

					new_node->Gender = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Gender, holder.Gender);

					new_node->Nationality = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Nationality, holder.Nationality);

					new_node->Religion = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Religion, holder.Religion);

					new_node->Occupation = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(new_node->Occupation, holder.Occupation);

					new_node->next = (hashTable[index]);
					hashTable[index] = new_node;
					num_terms++;

			}
			else if (hashTable[index] != NULL && strcmp(hashTable[index]->Surname, holder.Surname) != 0){
				//"Hash this to somewhere else
				while(hashTable[index] != NULL){
					index++;
					collisions++;
					if (index == ARRAY_SIZE){
						index = 0;
					}
				}
					hashTable[index] = malloc(sizeof(Element));
					hashTable[index]->Person_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Person_ID, holder.Person_ID);
					hashTable[index]->Deposition_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Deposition_ID, holder.Deposition_ID);
					hashTable[index]->Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Surname, holder.Surname);
					hashTable[index]->Forename = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Forename, holder.Forename);
					hashTable[index]->Age = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Age, holder.Age);
					hashTable[index]->Person_Type = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Person_Type, holder.Person_Type);
					hashTable[index]->Gender = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Gender, holder.Gender);
					hashTable[index]->Nationality = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Nationality, holder.Nationality);
					hashTable[index]->Religion = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Religion, holder.Religion);
					hashTable[index]->Occupation = malloc(sizeof(char)*MAX_STRING_SIZE);
					strcpy(hashTable[index]->Occupation, holder.Occupation);
					hashTable[index]->next = NULL;
					num_terms++;

			}
		}

	}

	// always remember to close your file stream
	fclose(f);

	return 1;
}

Element* search_lite(char* name){
	int index = hash(name);
	while(hashTable[index] != NULL)
	{
		if (strcmp(hashTable[index]->Surname, name) != 0){index++;}
		else{return hashTable[index];
}
	}
    return NULL;
}

void printData(char* name){
		Element* person = search_lite(name);
		while(person != NULL)
		{
			printf("%s	", person->Person_ID);
			printf("%s	", person->Deposition_ID);
			printf("%s	", person->Surname);
			printf("%s	", person->Forename);
			printf("%s	", person->Age);
			printf("%s	", person->Person_Type);
			printf("%s	", person->Gender);
			printf("%s	", person->Nationality);
			printf("%s	", person->Religion);
			printf("%s\n", person->Occupation);
			if (person->next == NULL){break;}
			else if (person->next != NULL){person = person->next;}
		}
}

int main()
{
	Element userInput;
	userInput.Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Person_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Deposition_ID = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Surname = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Forename = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Age = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Person_Type = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Gender = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Nationality = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Religion = malloc(sizeof(char)*MAX_STRING_SIZE);
	holder.Occupation = malloc(sizeof(char)*MAX_STRING_SIZE);

	int load_return = load_file("people.csv");
	if(load_return == 1){printf("File people.csv loaded!\n");}
	printf("Capacity: %d\n", ARRAY_SIZE);
	printf("Num Terms: %d\n", num_terms);
	printf("Collisions: %d\n", collisions);
	float load = ((float)num_terms / (float)ARRAY_SIZE);
	printf("Load: %f\n", load);
	printf("Enter term to get frequency or type \"quit\" to escape\n");
	while(strcmp(userInput.Surname, "quit") != 0)
		{
			printf(">>> ");
			printData("Surname");
			fgets(userInput.Surname, MAX_STRING_SIZE, stdin);		// this didn't work because it scanf terminates at a space
			userInput.Surname[strlen(userInput.Surname)-1]='\0';	// got this from https://stackoverflow.com/questions/51310985/remove-newline-from-fgets-input
																	// limits the whitespace read in by fgets
			printData(userInput.Surname);
		}
	for (int i = 0; i < ARRAY_SIZE; i++){
		free(hashTable[i]);
	}
    return 0;
}