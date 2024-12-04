#include <iostream>
using namespace std;

void display(int *parent, int *weight, int size)
{
    cout << "Node Parent weight \n";
    for (int i = 1; i < size; i++)
        cout << (parent[i] + 1) << "\t" << (i + 1) << "\t" << weight[i] << endl;
    cout << endl;
}

int minWeight(int *weightList, int *visited, int size)
{
    int minValue = INT32_MAX, minIndex;
    for (int i = 0; i < size; i++)
    {
        if (minValue > weightList[i] and !visited[i])
            minValue = weightList[i], minIndex = i;
    }
    return minIndex;
}

void mst(int **matrix, int size)
{
    int weightList[size], parent[size], visited[size];

    for (int i = 0; i < size; i++)
        weightList[i] = INT32_MAX, visited[i] = 0;

    // 1st node is  root
    // no parent and no weight
    weightList[0] = 0;
    parent[0] = -1;

    // visited only size - 1 times
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = minWeight(weightList, visited, size); // minimum value of row --> minimum weight of find of connected of particular node

        visited[minIndex] = 1;
        for (int j = 0; j < size; j++)
            if (matrix[minIndex][j] and matrix[minIndex][j] < weightList[j] and !visited[j])
            {
                weightList[j] = matrix[minIndex][j];
                parent[j] = minIndex;
            }
    }

    display(parent, weightList, size);
}

int main()
{
    int size, sizeNode, node, w;
    int **matrix;

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
        cout << "Enter number of nodes connected with " << (i + 1) << " node of graph : ";
        cin >> sizeNode;
        sizeNode &&cout << "Enter all nodes and weight :\n";
        for (int j = 0; j < sizeNode; j++)
        {
            cout << "Node and Weight :\n";
            cin >> node >> w;
            matrix[i][node - 1] = w;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    mst(matrix, size);
    return 0;
}