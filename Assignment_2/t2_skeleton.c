#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void selectionSort(int arr[], int size)
{
	int smallest = arr[0];
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[i])
			{
				smallest = arr[j];
				arr[j] = arr[i];
				arr[i] = smallest;
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
		if (i > 0){candidate = arr[i - 1];}
		if (arr[i] < candidate)
		{
			candidate = arr[i];
			candidate_positon = i;
			for (int j = i - 1; j >= 0; j--)
				{
					if (arr[j] > candidate)
					{
						holder = arr[j];
						arr[j] = candidate;
						arr[candidate_positon] = holder;
						candidate_positon --;
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

void quickSort(int arr[], int size)
{
  srand(time(NULL));
  quicksort_recursion(arr, 0, size - 1);
}

void quickSort_recursion(int array[], int low, int high)
{
  if (low < high)
  {
    int pivot_index = partition(array, low, high);
    quickSort_recursion(array, low, pivot_index - 1);
    quickSort_recursion(array, pivot_index + 1, high);
  }
}

int partition(int array[], int low, int high)
{
  int pivot_index = low + (rand() % (high - low));
  
  if (pivot_index != high)
    swap(&array[pivot_index], &array[high]);
  
  int pivot_value = array[high];
  int i = low; 

  for (int j = low; j < high; j++)
  {
    if (array[j] <= pivot_value)
    {
      swap(&array[i], &array[j]);
      i++;
    }
  }
  swap(&array[i], &array[high]);
  return i;
}