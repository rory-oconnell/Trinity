#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char number[200];
    char name[200];
    char type1[200];
    char type2[200];
    char total[200];
    char hp[200];
    char attack[200];
    char defense[200];
    char sp_attack[200];
    char sp_defense[200];
    char speed[200];
    char generation[200];
    char legendary[200];
    char description[500];
}   Pokemon;

char FEEDER[500];
int LENGTH = 700;
int FIELDS = 13;
int feeder_count = 0;
int attribute_index = 0;
Pokemon monsters[700];

char filename[100];

int main(int argc, char* argv[])
{

    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./read_csv file_name.csv\n");
        return 1;
    }

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
        for (int i = 0; i < sizeof(monsters); i++)
        {
            while(!feof(pf)) //continue to read the file so long as we have not(!) reached the end of the file
                {
                    ch = fgetc(pf);

                    // printf("%c", ch);
                    // printf("%i", ch);
                    // printf("%d", ch);

                    int ch_as_int = (int) ch;   //the ascii value of the read character

                    if (ch_as_int == -1)    //used debugger and found that the last character has an ascii value of -1.
                    {
                        ;   //program was printing diamond question mark at this point so I instead instucted it to do nothing.
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
                            ;
                        }
                        else
                        {
                            ;
                        }
                    }

                    else if (ch_as_int == 34)
                        {
                            quotation_counter++;    //keep track of the quotation marks

                            if (quotation_counter == 2)
                            {
                                quotation_counter = 0;
                            }
                        }

                    else
                    {
                            FEEDER[feeder_count] = ch;
                            feeder_count++;
                    }

                        }

                            if (attribute_index == 0)   //keeps track of what attribute we are changing
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].number[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 1)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].name[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 2)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].type1[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 3)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].type2[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 4)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].total[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 5)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].hp[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 6)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].attack[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 7)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].defense[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 8)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].sp_attack[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 9)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].sp_defense[j] = FEEDER[j];
                                };
                            }
                            else if (attribute_index == 10)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].speed[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 11)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].generation[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 12)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 44)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].legendary[j] = FEEDER[j];
                                }
                            }
                            else if (attribute_index == 13)
                            {
                                for (int j = 0; j < sizeof(FEEDER); j++)
                                {
                                    if ((int)FEEDER[j] == 10)
                                    {
                                        attribute_index++;
                                        feeder_count = 0;
                                        break;
                                    }
                                    else
                                    monsters[i].description[j] = FEEDER[j];
                                }
                            }
                        }
                    printf("\n\n");
                    fclose(pf);
                }
            return 0;
        }