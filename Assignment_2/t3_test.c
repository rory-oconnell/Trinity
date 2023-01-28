#include "t1.h"
#include "t2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
void quicksort(int array[], int length);
void quicksort_recursion(int array[], int low, int high);
int partition(int array[], int low, int high);
void fill_ascending(int *array, int size);
void fill_descending(int *array, int size);
void fill_uniform(int *array, int size);
void fill_with_duplicates(int *array, int size);
void fill_without_duplicates(int *array, int size);
int is_sorted(int* array, int size);
void print_test_headers();
void print_test_results(char* test_name, int sorted,  int num_swaps, int num_comparisons);
void test_and_print_for_given_array(void (*f) (int*,int), int size, int* array, char* test_name);
void test_all_arrays_of_given_size(void (*f) (int*,int), int size);
void test_all_functions_for_given_size(int size);

int number_comparisons = 0;
int number_swaps = 0;

int main()
{

    test_all_functions_for_given_size(10000);

    return 0;
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
          array[i] = rand() % 10000;
      }
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    int new_random;
    int unique = 1;

    for (int i = 0; i < size; i++)
    {
        do
        {
            new_random = (rand() % 10000);

            unique = 1;
            for (int j = 0; j < i; j++)
                if (array[j] == new_random) unique = 0;
        } 
        while (unique == 0);

        array[i] = new_random;
    }
}

int is_sorted(int* array, int size)
{
    int i=0;
	for( i=0; i<size-1; i++ ) {
		if( array[i] > array[i+1] ) {
            printf("unsorted\n");
            return 0;
        }
	}
     printf("sorted\n");
	return 1;
}

void print_test_headers()
{
    int n =10; // column width
    int n_first =25; //first column width
    printf("%*s | %*s | %*s | %*s |\n", n_first, "TEST", n, "SORTED", n, "SWAPS", n, "COMPS");
}

void print_test_results(char* test_name, int sorted,  int num_swaps, int num_comparisons)
{
    int n =10; // column width
    int n_first =25; //first column width
    printf("%*s | %*s | %*d | %*d |\n",n_first, test_name, n, sorted? "YES" : "NO", n, num_swaps, n, num_comparisons);

}

void test_and_print_for_given_array(void (*f) (int*,int), int size, int* array, char* test_name)
{
    number_comparisons = 0;
    number_swaps = 0;
    (*f)(array, size);
    print_test_results( test_name, is_sorted(array,size),number_swaps,number_comparisons);
}

void test_all_arrays_of_given_size(void (*f) (int*,int), int size)
{

    print_test_headers();

    int* array =  malloc(size * sizeof(int));

    fill_ascending(array,size);
    test_and_print_for_given_array(f,size, array, "Ascending");


    fill_descending(array,size);
    test_and_print_for_given_array(f,size, array, "Descending");


    fill_uniform(array,size);
    test_and_print_for_given_array(f,size, array, "Uniform");


    fill_with_duplicates(array,size);
    test_and_print_for_given_array(f,size, array, "Random w duplicates");


    fill_without_duplicates(array,size);
    test_and_print_for_given_array(f,size, array, "Random w/o  duplicates");

    printf("\n\n");


}

void test_all_functions_for_given_size(int size){
    printf("Arrays of size %d: \n", size);
    printf("  Selection sort\n");
    test_all_arrays_of_given_size(selectionSort, size);
    printf("  Insertion sort\n");
    test_all_arrays_of_given_size(insertionSort, size);
    printf("  Quick sort\n");
    test_all_arrays_of_given_size(quickSort, size);
    printf("\n\n");

}

void selectionSort(int arr[], int size)
{
	int smallest = arr[0];
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
      number_comparisons++;
			if (arr[j] < arr[i])
			{
				smallest = arr[j];
				arr[j] = arr[i];
				arr[i] = smallest;
        number_swaps++;
			}
		}
	}
}

void insertionSort(int arr[], int size)
{	
	int candidate = arr[0];
	int candidate_positon;
	int holder;

	for (int i = 0; i < size; i++)
	{
    number_comparisons++;
		if (i > 0){candidate = arr[i - 1];}
		if (arr[i] < candidate)
		{
			candidate = arr[i];
			candidate_positon = i;
			for (int j = i - 1; j >= 0; j--)
				{
          number_comparisons++;
					if (arr[j] > candidate)
					{
						holder = arr[j];
						arr[j] = candidate;
						arr[candidate_positon] = holder;
						candidate_positon --;
            number_swaps++;
					}
				}
		}
	}
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partition(int array[], int low, int high)
{
  int pivot_index = low + (rand() % (high - low));
  
  if (pivot_index != high)
  {
    swap(&array[pivot_index], &array[high]);
    number_swaps++;
  }
  
  int pivot_value = array[high];
  int i = low; 

  for (int j = low; j < high; j++)
  {
    number_comparisons++;
    if (array[j] <= pivot_value)
    {
      swap(&array[i], &array[j]);
      number_swaps++;
      i++;
    }
  }
  swap(&array[i], &array[high]);
  number_swaps++;
  return i;
}

void quicksort_recursion(int array[], int low, int high)
{
  if (low < high)
  {
    int pivot_index = partition(array, low, high);
    quicksort_recursion(array, low, pivot_index - 1);
    quicksort_recursion(array, pivot_index + 1, high);
  }
}

void quickSort(int arr[], int size)
{
  srand(time(NULL));
  quicksort_recursion(arr, 0, size - 1);
}