#include <iostream>
using namespace std;

class listADT;
class Node
{
    int data;
    Node *next;

public:
    Node(int d)
    {
        data = d;
        next = nullptr;
    }
    friend class listADT;
};

class listADT
{
    Node *head;
    Node *tail;

public:
    listADT() { head = nullptr; }
    void insertAtBegin(int value)
    {
        Node *ptr = new Node(value);
        if (head == nullptr)
        {
            head = ptr;
            tail = ptr;
        }
        else
        {
            ptr->next = head;
            head = ptr;
        }
    }
    void insertAtEnd(int value)
    {
        Node *ptr = new Node(value);
        if (head == nullptr)
        {
            head = ptr;
            tail = ptr;
        }
        else
        {
            tail->next = ptr;
            tail = ptr;
        }
    }

    int deleteAtBegin()
    {
        Node *p = head;
        int d = p->data;
        if (head == nullptr)
        {
            cout << "List ADT is Empty\n";
            return -1;
        }
        else
        {
            head = head->next;
            delete p;
        }
        return d;
    }

    void display()
    {
        Node *p = head;
        while (p)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

int main()
{
    listADT l;
    l.insertAtBegin(45);
    l.insertAtBegin(23);
    l.insertAtBegin(78);
    l.insertAtBegin(69);

    l.insertAtEnd(234);
    l.insertAtEnd(676);
    l.insertAtEnd(768);
    l.insertAtEnd(124);

    l.display();
    return 0;
}