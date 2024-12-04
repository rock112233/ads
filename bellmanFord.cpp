#include <iostream>
using namespace std;

int *bellmanFord(int **arr, int size)
{
    int weightList[size];
    for (int i = 0; i < size; i++)
        weightList[i] = INT32_MAX;

    weightList[0] = 0;

    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (arr[j][k] != 0 and arr[j][k] + weightList[j] < weightList[k])
                    weightList[k] = arr[j][k] + weightList[j];
    return weightList;
}

void display(int weightList[], int size)
{
    cout << "Nodes Distance :\n";
    for (int i = 0; i < size; i++)
        cout << i << "\t" << weightList[i] << endl;
}

int main()
{
    int size, sizeNode, node, w;
    int **matrix;
    int *weightList;
    cout << "Enter number of nodes in graph : ";
    cin >> size;

    matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;

    for (int i = 0; i < size; i++)
    {
        cout << "Enter number of nodes connected with " << i << " node of graph : ";
        cin >> sizeNode;
        sizeNode &&cout << "Enter all nodes and weight :\n";
        for (int j = 0; j < sizeNode; j++)
        {
            cout << "Node and Weight :\n";
            cin >> node >> w;
            matrix[i][node] = w;
        }
    }
    weightList = bellmanFord(matrix, size);
    display(weightList, size);
    return 0;
}