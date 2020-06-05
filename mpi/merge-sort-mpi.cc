#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <mpi.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

void merge(int *, int, int, int);

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
    int i, j, k, c[high + 1];
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
    while (i <= mid)
    {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        arr[i] = c[i];
    }
}

void
run_root_mpi (int a[], int size, int temp[], int max_rank, int tag,
	      MPI_Comm comm)
{
  int my_rank;
  MPI_Comm_rank (comm, &my_rank);
  if (my_rank != 0)
    {
      printf
	("Error: run_root_mpi called from process %d; must be called from process 0 only\n",
	 my_rank);
      MPI_Abort (MPI_COMM_WORLD, 1);
    }
  mergesort_parallel_mpi (a, size, temp, 0, my_rank, max_rank, tag, comm);
  /* level=0; my_rank=root_rank=0; */
  return;
}

// Helper process code
void
run_helper_mpi (int my_rank, int max_rank, int tag, MPI_Comm comm)
{
  int level = my_topmost_level_mpi (my_rank);
  // probe for a message and determine its size and sender
  MPI_Status status;
  int size;
  MPI_Probe (MPI_ANY_SOURCE, tag, comm, &status);
  MPI_Get_count (&status, MPI_INT, &size);
  int parent_rank = status.MPI_SOURCE;
  // allocate int a[size], temp[size] 
  int *a = malloc (sizeof (int) * size);
  int *temp = malloc (sizeof (int) * size);
  MPI_Recv (a, size, MPI_INT, parent_rank, tag, comm, &status);
  mergesort_parallel_mpi (a, size, temp, level, my_rank, max_rank, tag, comm);
  // Send sorted array to parent process
  MPI_Send (a, size, MPI_INT, parent_rank, tag, comm);
  return;
}

// Given a process rank, calculate the top level of the process tree in which the process participates
// Root assumed to always have rank 0 and to participate at level 0 of the process tree
int
my_topmost_level_mpi (int my_rank)
{
  int level = 0;
  while (pow (2, level) <= my_rank)
    level++;
  return level;
}

// MPI merge sort
void
mergesort_parallel_mpi (int a[], int size, int temp[],
			int level, int my_rank, int max_rank,
			int tag, MPI_Comm comm)
{
  int helper_rank = my_rank + pow (2, level);
  if (helper_rank > max_rank)
    {				// no more processes available
      merge_sort(data, 0, numLines - 1);
      merge_sort (a, size, temp);
    }
  else
    {
//printf("Process %d has helper %d\n", my_rank, helper_rank);
      MPI_Request request;
      MPI_Status status;
      // Send second half, asynchronous
      MPI_Isend (a + size / 2, size - size / 2, MPI_INT, helper_rank, tag,
		 comm, &request);
      // Sort first half
      mergesort_parallel_mpi (a, size / 2, temp, level + 1, my_rank, max_rank,
			      tag, comm);
      // Free the async request (matching receive will complete the transfer).
      MPI_Request_free (&request);
      // Receive second half sorted
      MPI_Recv (a + size / 2, size - size / 2, MPI_INT, helper_rank, tag,
		comm, &status);
      // Merge the two sorted sub-arrays through temp
      merge (a, size, temp);
    }
  return;
}

int main(int argc, char *argv[])
{

    int numLines = 0;
    ifstream in(argv[1]);
    string unused;

    while (getline(in, unused))
    {
        ++numLines;
    }

    int data[numLines];

    ifstream input(argv[1]);
    for (int i = 0; i < numLines; i++)
    {
        input >> data[i];
    }

    merge_sort(data, 0, numLines - 1);
    string argv1(argv[1]);
    string result = "result_" + argv1;
    ofstream myfile(result.c_str());

    if (myfile.is_open())
    {

        for (int i = 0; i < numLines; i++)
        {
            myfile << data[i] << "\n";
        }

        myfile.close();
    }
    else
        cout << "No se pudo abrir el archivo";

    // All processes
    MPI_Init(&argc, &argv);
    // Check processes and their ranks
    // number of processes == communicator size
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int max_rank = comm_size - 1;
    int tag = 123;
    // Set test data
    if (my_rank == 0)
    { // Only root process sets test data
        puts("-MPI Recursive Mergesort-\t");
        // Check arguments
        if (argc != 2) /* argc must be 2 for proper execution! */
        {
            printf("Usage: %s test_*\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        // Get argument
        int size = numLines; // Array size
        printf("Array size = %d\nProcesses = %d\n", size, comm_size);
        // Array allocation
        int *a = malloc(sizeof(int) * size);
        int *temp = malloc(sizeof(int) * size);
        if (a == NULL || temp == NULL)
        {
            printf("Error: Could not allocate array of size %d\n", size);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        // Random array initialization
        srand(314159);
        int i;
        for (i = 0; i < size; i++)
        {
            a[i] = data[i];
        }
        // Sort with root process
        double start = get_time();
        run_root_mpi(a, size, temp, max_rank, tag, MPI_COMM_WORLD);
        double end = get_time();
        printf("Start = %.2f\nEnd = %.2f\nElapsed = %.2f\n",
               start, end, end - start);
        // Result check
        for (i = 1; i < size; i++)
        {
            if (!(a[i - 1] <= a[i]))
            {
                printf("Implementation error: a[%d]=%d > a[%d]=%d\n", i - 1,
                       a[i - 1], i, a[i]);
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }
    } // Root process end
    else
    { // Helper processes
        run_helper_mpi(my_rank, max_rank, tag, MPI_COMM_WORLD);
    }
    fflush(stdout);
    MPI_Finalize();
    return 0;
}
