#include <stdio.h>

typedef struct
{
    int number;
    char name[50];  //assuming name will not be longer than 49 characters, as we need one character for the null terminator
    char type1[20];
    char type2[20];
    int total;
}   Pokemon;

int main(void)
{
    FILE *file; //creation of a file pointer variable

    file = fopen("pokemon_small.csv", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    Pokemon monsters[650];  //we can store up to 650 pokemon students in this array

    int read = 0;   //store the number of values that were read in successfully
    int records = 0;    //number of records read into the file
    int exlcude_first_line = 0;

    do
    {
        read = fscanf(file,
        "%d,%49[^,],%20[^,],%20[^,],%d,\n",      //fscanf returns the number of values that it was able to read in successfully
        &monsters[records].number,    //records is keeping track of how many records were read in from the file. also used to keep track of current position
        monsters[records].name,
        monsters[records].type1,
        monsters[records].type2,
        &monsters[records].total
        );

        if (read == 5) records ++;

        if (read != 5 && !feof(file))
        {
            printf("Fields missing.\n");
        }

        if (ferror(file))
        {
            printf("Error reading file.\n");
            return 1;
        }

    } while(!feof(file)); //continue to read the file so long as we have not(!) reached the end of the file

    fclose(file);

    printf("\n%d records read. \n\n", records);

    for (int i = 0; i < records; i++)
    {
        printf("%d %s %s %s %d\n",
        monsters[i].number,
        monsters[i].name,
        monsters[i].type1,
        monsters[i].type2,
        monsters[i].total
        );
    printf("\n");

    }

    return 0;
}