#include <iostream>
#include <random>
#include <ctime>
using namespace std;

void display(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int partition(int *arr, int high, int low)
{
    int i = low;
    int j = high;
    int pivot = rand() % (high - low + 1) + low;
    swap(arr[i], arr[pivot]);
    pivot = low;

    do
    {
        while (arr[i] <= arr[pivot])
            i++;
        while (arr[j] > arr[pivot])
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    } while (i < j);
    swap(arr[j], arr[pivot]);
    return j;
}

int quickSort(int *arr, int high, int i, int low = 0)
{
    if (high == low)
        return arr[low];

    int q = partition(arr, high, low);
    int k = q - low + 1;

    if (i == k)
        return arr[q];
    else if (i < k)
        return quickSort(arr, q - 1, i, low);
    else
        return quickSort(arr, high, i-k, q + 1);
}

int main()
{
    int size = 10;
    int arr[size];

    // Random elements array
    static mt19937 gen(time(0)); // Pseudo Random Generator
    static uniform_int_distribution<int> distr(100, 1000);
    for (int i = 0; i < size; i++)
        arr[i] = distr(gen);

    // Custom elements array
    // cout << "Enter here.... \n";
    // for (int i = 0; i < size; i++)
    //     cin >> arr[i];

    int i = 4;
    display(arr, size);
    cout << "Position " << i << " of array value is : " << quickSort(arr, size - 1, i);

    return 0;
}