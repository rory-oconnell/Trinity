#include <stdlib.h>
#include <stdio.h>

char filename[100];

void load_csv(char* argv[1]);

int main(int argc, char* argv[])
{

    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./read_csv file_name.csv\n");
        return 1;
    }

    load_csv(argv[1]);
    return 0;

}

load_csv(char* argv[1])
{
    FILE *pf = fopen(argv[1], "r");
    char ch; //need a variable of type char to store the characters that are being read
    int quotation_counter = 0;
    int exclude_first_line_counter = 0; //the dumbest way possible to skip the first line. if an LS ascii 10 has not been read, don't print anything.

    if (pf == NULL) //if the file is not read successfully, exit the program.
    {
        printf("Error encountered; unable to read file...");
        return 1;
    }

    else
    {
        while(!feof(pf))                //continue to read the file so long as we have not(!) reached the end of the file
        {
            ch = fgetc(pf);
            int ch_as_int = (int) ch;   //the ascii value of the read character
            if (ch_as_int == -1)        //used debugger and found that the last character has an ascii value of -1.
            {
                ;                       //program was printing diamond question mark at this point so I instead instucted it to do nothing.
            }

            else if (ch_as_int == 10)
            {
                exclude_first_line_counter++;
                if (exclude_first_line_counter > 1)
                {
                    printf("\n\n");
                }
            }

            else if (exclude_first_line_counter < 1)
            {
                ;
            }

            else if (ch_as_int == 44)    //if a comma is encountered
            {
                if (quotation_counter == 0) //check to see if we are inside quotations
                {
                    printf(" \n");
                }
                else
                {
                    printf("%c", ch);
                }
            }
            else if (ch_as_int == 34)
                {
                    quotation_counter++;    //keep track of the quotation marks - replace with a boolean?
                    if (quotation_counter == 2)
                    {
                        quotation_counter = 0;
                    }
                }
            else
                {
                    printf("%c", ch);
                }
        }
        printf("\n\n");
        fclose(pf);
    }

}
