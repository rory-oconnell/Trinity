#include <stdio.h>

typedef struct
{
    char type;
    char name[50];  //assuming name will not be longer than 49 characters, as we need one character for the null terminator
    int age;
    double average;
}   Student;

int main(void)
{
    FILE *file; //creation of a file pointer variable

    file = fopen("athletes.csv", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    Student students[100];  //we can store up to 100 students in this array

    int read = 0;   //store the number of values that were read in successfully
    int records = 0;    //number of records read into the file
    int exlcude_first_line = 0;

    do
    {
        read = fscanf(file,
        "%c,%49[^,],%d,%lf\n", //fcanf returns the number of values that it was able to read in successfully
        &students[records].type,    //records is keeping track of how many records were read in from the file. also used to keep track of current position
        students[records].name,     //don't need & to pass in the memory address because name is an array. when using an array as an argument to a function, it decays to a pointer
        &students[records].age,
        &students[records].average);

        if (read == 4) records ++;

        if (read != 4 && !feof(file))
        {
            printf("File format incorrect.\n");
            return 1;
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
        printf("%c %s %d %.2f\n",
        students[i].type,
        students[i].name,
        students[i].age,
        students[i].average);
    printf("\n");

    }

    return 0;
}