#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int i = 0;

int main(void)
{
	char word[256];					                    // Creating a space to hold out input
	printf("Please input the word to be sorted\n");     // Prompting the user for input
	fgets(word, 256, stdin);		                    // Getting input from the user
	printf("%s\n", word);								// Print the input word

	while (isalnum(word[i]))
    {
		printf("%c\n", word[i]);
		i++;
    }
}