#include <iostream>
#include <random>
#include <ctime>
using namespace std;
int count = 0;

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
    swap(arr[i],arr[pivot]);
    pivot = low;

    do
    {
        while (arr[i] <= arr[pivot])
            i++;
        while (arr[j] > arr[pivot])
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
        count++;
    } while (i < j);
    swap(arr[j], arr[pivot]);
    return j;
}

void quickSort(int *arr, int high, int low = 0)
{
    if (low < high)
    {
        int p = partition(arr, high, low);
        quickSort(arr, p - 1, low);
        quickSort(arr, high, p + 1);
    }
}

int main()
{

    int size = 30;
    int arr[size];

    // Random elements array
    static mt19937 gen(time(0));
    static uniform_int_distribution<int> distr(100, 1000);
    for (int i = 0; i < size; i++)
        arr[i] = distr(gen);

    // Custom elements array
    // cout << "Enter here.... \n";
    // for (int i = 0; i < size; i++)
    //     cin >> arr[i];

    cout << "Before Sort :\n";
    display(arr, size);
    quickSort(arr, size - 1);
    cout << "After Sort :\n";
    display(arr, size);

    cout << "No. of Swap's : " << count << endl;
    return 0;
}