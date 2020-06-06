#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <mpi.h>
#include <omp.h>
#include "merge-sort.h"


using namespace std;

void merge_sort_parallel(int *original_array, int n, int argc, char** argv)
{
<<<<<<< HEAD
=======
	
	/********** Initialize MPI **********/
	int world_rank;
	int world_size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
>>>>>>> 0eb4d6a11edcb033d61275be762d405550300ce5
		

void merge_sort(int *arr, int low, int high)
{
    int mid;
    if (low < high)
    {
        //divide el arreglo a la mitad y ordena independientemente usando merge sort
        mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        //combina o fusiona los arreglos ordenados
        merge(arr, low, high, mid);
    }
}

// Merge sort
void merge(int *arr, int low, int high, int mid)
{
    int i, j, k, c[high+1];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            c[k] = arr[j];
            k++;
            j++;
        }
    }

    #pragma omp parallel for
    for(int x = i; x<=mid ;x++){
        #pragma omp critical
        {
        c[k] = arr[x];
        k++;
        }
    }
    #pragma omp parallel for
    for(int y = j; y<=high ;y++){
        #pragma omp critical
        {
        c[k] = arr[y];
        k++;
        }
    }
    #pragma omp parallel for
    for (i = low; i < k; i++) {
        #pragma omp critical
        {
        arr[i] = c[i];
        }
    }
}