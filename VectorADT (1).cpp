#include <iostream>
using namespace std;

class vectorADT
{
    int *arr;
    int n, capcity;

public:
    vectorADT(int cap = 10)
    {
        capcity = cap;
        n = 0;
        arr = new int[capcity];
    }
    ~vectorADT() { delete arr; }

    int size() { return n; }
    bool isEmpty() { return n == 0; }
    bool isFull() { return n == capcity; }

    void insertAtBegin(int value)
    {
        if (isFull())
        {
            cout << "Array is Full\n";
            return;
        }
        for (int i = n - 1; i >= 0; i--)
            arr[i + 1] = arr[i];
        arr[0] = value;
        n++;
    }

    void insertAtEnd(int value)
    {
        if (isFull())
        {
            cout << "Array is Full\n";
            return;
        }
        arr[n++] = value;
    }

    void insertAtrank(int rank, int value)
    {
        if (isFull())
        {
            cout << "Array is full\n";
            return;
        }
        if (rank < 0 && rank > capcity)
        {
            cout << "Rank out of range\n";
            return;
        }
        for (int i = n - 1; i >= rank; i--)
            arr[i + 1] = arr[i];
        arr[rank] = value;
        n++;
    }

    void replaceAtRank(int rank, int value)
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return;
        }
        if (rank < 0 && rank > n)
        {
            cout << "Rank out of range\n";
            return;
        }
        arr[rank] = value;
    }

    int deleteAtBegin()
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        int value = arr[0];
        for (int i = 0; i < n - 1; i++)
            arr[i] = arr[i + 1];
        n--;
        return value;
    }

    int deleteAtEnd()
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        n--;
        return arr[n];
    }

    int deleteAtrank(int rank)
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        if (rank < 0 && rank > n)
        {
            cout << "rank out of range\n";
            return -1;
        }
        int value = arr[rank];
        for (int i = rank; i < n; i++)
            arr[i] = arr[i + 1];
        n--;
        return value;
    }

    int valueAtRank(int rank)
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        if (rank < 0 && rank > n)
        {
            cout << "rank out of range\n";
            return -1;
        }
        return arr[rank];
    }

    void swapValue(int sourcerank, int destrank)
    {
        if ((sourcerank < 0 && sourcerank > n) || (destrank < 0 && destrank > n))
        {
            cout << "rank out of range\n";
            return;
        }
        swap(arr[sourcerank], arr[destrank]);
    }

    int sumArr()
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        int s = 0;
        for (int i = 0; i < n; i++)
            s += arr[i];
        return s;
    }

    int maxValue()
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        int maxval = arr[0];
        for (int i = 0; i < n; i++)
            if (maxval < arr[i])
                maxval = arr[i];
        return maxval;
    }
    int minValue()
    {
        if (isEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        int minval = arr[0];
        for (int i = 0; i < n; i++)
            if (minval > arr[i])
                minval = arr[i];
        return minval;
    }

    void reverse()
    {
        if (isEmpty())
        {
            cout << "Array is empty\n";
            return;
        }
        for (int i = 0; i < n / 2; i++)
            swap(arr[i], arr[n - 1 - i]);
    }

    void display()
    {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    vectorADT v;
    // cout << "--> Insert at Begin\n";
    // v.insertAtBegin(40);
    // v.insertAtBegin(56);
    // v.insertAtBegin(53);
    // v.insertAtBegin(45);
    // v.display();

    // cout << "--> Insert at End\n";
    // v.insertAtEnd(2);
    // v.insertAtEnd(6);
    // v.insertAtEnd(4);
    // v.insertAtEnd(8);
    // v.display();

    // cout << "--> Insert at rank\n";
    // v.insertAtrank(4, 678);
    // v.insertAtrank(4, 308);
    // v.insertAtrank(7, 208);
    // v.display();

    // cout << "--> Element Replace with rank\n";
    // v.display();
    // v.replace(3, 65768);
    // v.display();

    // cout << "--> Delete at Begin\n";
    // v.display();
    // cout << v.deleteAtBegin() << endl;
    // v.display();

    // cout << "--> Delete at End\n";
    // v.display();
    // cout << v.deleteAtEnd() << endl;
    // v.display();

    // cout << "--> Delete at rank\n";
    // v.display();
    // cout << v.deleteAtrank(3) << endl;
    // v.display();

    // cout << "--> Value at rank\n";
    // cout << v.valueAt(2) << endl;
    // v.display();

    // cout << "--> Swap Values in array\n";
    // v.display();
    // v.swapValue(2, 5);
    // v.display();

    // cout << "--> Sum of Array\n";
    // cout << v.sumArr() << endl;

    // cout << "--> Max Value in Array\n";
    // cout << v.maxValue() << endl;

    // cout << "--> Min Value in Array\n";
    // cout << v.minValue() << endl;

    // cout << "--> Peek Value in Array\n";
    // cout << v.peek() << endl;

    // cout << "--> Reverse of Array\n";
    // v.insertAtBegin(13);
    // v.display();
    // v.reverse();
    // v.display();

    int option, value, rank, rank2;

    while (true)
    {
        cout << "Select any one : \n"
             << "1. Insert at Begin \n"
             << "2. Insert at End \n"
             << "3. Insert at Rank \n"
             << "4. Replace at Rank \n"
             << "5. Delete at Begin \n"
             << "6. Delete at End \n"
             << "7. Delete at Rank \n"
             << "8. Value at Rank \n"
             << "9. Swap two value at rank's \n"
             << "10. Sum of Array \n"
             << "11. Maximum Value of Array \n"
             << "12. Minimum Value of Array \n"
             << "13. Reverse of Array \n"
             << "14. Display Array \n"
             << "0. Exit \n";
        cin >> option;
        if (option == 1)
        {
            cout << "Enter value : ";
            cin >> value;
            v.insertAtBegin(value);
        }
        else if (option == 2)
        {
            cout << "Enter value : ";
            cin >> value;
            v.insertAtEnd(value);
        }
        else if (option == 3)
        {
            cout << "Enter value : ";
            cin >> value;
            cout << "Enter Rank : ";
            cin >> rank;
            v.insertAtrank(rank, value);
        }
        else if (option == 4)
        {
            cout << "Enter value : ";
            cin >> value;
            cout << "Enter Rank : ";
            cin >> rank;
            v.replaceAtRank(rank, value);
        }
        else if (option == 5)
            cout << v.deleteAtBegin() << endl;
        else if (option == 6)
            cout << v.deleteAtEnd() << endl;
        else if (option == 7)
        {
            cout << "Enter Rank : ";
            cin >> rank;
            cout << v.deleteAtrank(rank) << endl;
        }
        else if (option == 8)
        {
            cout << "Enter Rank : ";
            cin >> rank;
            cout << v.valueAtRank(rank) << endl;
        }
        else if (option == 9)
        {
            cout << "Enter source Rank : ";
            cin >> rank;
            cout << "Enter destination Rank : ";
            cin >> rank2;
            v.swapValue(rank, rank2);
        }
        else if (option == 10)
            cout << "Sum of Array : " << v.sumArr() << endl;
        else if (option == 11)
            cout << "Maximum Value of Array : " << v.maxValue() << endl;
        else if (option == 12)
            cout << "Minimum Value of Array : " << v.minValue() << endl;
        else if (option == 13)
            v.reverse();
        else if (option == 14)
            v.display();
        else if (option == 0)
            break;
        else
            cout << "Invalid option will be select \n";
    }

    return 0;
}