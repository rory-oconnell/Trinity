#include <stdlib.h>
#include <stdio.h>

char array[20];

int main(void)
{
    for (int i = 0; i < sizeof(array); i++)
    {
        int ch_as_int = (int) array[i];
        printf("%d\n", ch_as_int);
        printf("%c\n", array[i]);

    }

    return 0;
}