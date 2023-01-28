#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_ascending(int *array, int size);
void fill_descending(int *array, int size);
void fill_uniform(int *array, int size);
void fill_with_duplicates(int *array, int size);
void fill_without_duplicates(int *array, int size);
void printArray(int* arr, int size);


int main()
{
    int testarray[9];
    fill_without_duplicates(testarray, 9);
    printArray(testarray, 9);
}

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    for (int i = 0; i < size; i++){array[i] = i;}
}

//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    for (int i = 0; i < size; i++){array[i] = (size - 1 - i);}
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    srand(time(NULL));
    int randomnumber;
    randomnumber = rand() % 10;
    for (int i = 0; i < size; i++){
        array[i] = randomnumber;
    }
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
      srand(time(NULL));
      for (int i = 0; i < size; i++) {
          array[i] = rand() % 10;
      }
}

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
      srand(time(NULL));
      for (int i = 0; i < size; i++)
      {
        array[i] = rand() % 10;
        for (int j = 0; j < i; j++)
        {
            if (i == 0){break;}
            if (array[i] == array[j]){
                array[i] = rand() % 10;
                j = 0;
            }
        }
      }
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}
