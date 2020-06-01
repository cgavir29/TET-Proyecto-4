#include <fstream>
#include <iostream>

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
    int i, j, k, c[50];
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

int main()
{
    int numLines = 0;
    ifstream in("test.txt");
    string unused;
    while (getline(in, unused))
    {
        ++numLines;
    }

    int data[numLines];

    ifstream input("test.txt");
    for (int i = 0; i < numLines; i++)
    {
        input >> data[i];
    }

    merge_sort(data, 0, numLines - 1);

    ofstream myfile("result.txt");
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
}
