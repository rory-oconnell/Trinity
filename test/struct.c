#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int number;
    char name[50];
}node;

int sample_number = 300;
char sample_name[20] = {'1'};

int main(void)
{
    node nodes[10];

    for (int i = 0; i < sizeof(nodes); i++)
    {
        nodes[i].number = sample_number;
        for (int j = 0; j < sizeof(sample_name); j++)
        {
            nodes[i].name[j] = sample_name[j];
        }
    }

    return 0;
}