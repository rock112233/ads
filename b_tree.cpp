#include <iostream>
using namespace std;

class BTree;
class BTreeNode
{
    int *arr;  // array of keys
    int n;     // current no fo keys
    bool leaf; // true if is leaf node, otherwise false
    int total;
    int childN;        // no of child of node
    BTreeNode **child; // array of child
public:
    BTreeNode(int total = 1, bool leaf = true)
    {
        this->total = total;
        arr = new int[total + 1];
        child = new BTreeNode *[total + 1];
        n = -1;
        childN = 0;
        this->leaf = leaf;
        for (int i = 0; i < total; i++)
            child[i] = 0;
    }

    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int minKey;
    int maxKey;

public:
    BTree(int min = 2, int max = 3)
    {
        minKey = min;
        maxKey = max;
        root = nullptr;
    }
    ~BTree() { delete root; }

    void insert(int key)
    {
        if (root == nullptr)
        {
            BTreeNode *ptr = new BTreeNode(maxKey, true);
            root = ptr, root->arr[0] = key, root->n++;
        }
        else
        {
            int index;
            BTreeNode *p = root;

            if (p->n <= maxKey and p->leaf)
                sortNodeKeys(p, key);
            if (p->n == maxKey and p == root)
                splitParent(p);
            else if (!p->leaf)
            {
                index = p->n;
                for (int i = 0; i <= p->n; i++)
                    if (key < p->arr[i])
                    {
                        index = i;
                        break;
                    }
                p->arr[index] > key ? index : index++;

                if (p->child[index]->leaf)
                    sortNodeKeys(p->child[index], key);
                else if (!p->child[index]->leaf)
                    insertKey(p->child[index], key);
                arrangeSplit(root);
            }
        }
    }

    void splitParent(BTreeNode *p)
    {
        static int flag = 0;
        BTreeNode *left = new BTreeNode(maxKey);
        BTreeNode *right = new BTreeNode(maxKey);

        int x;
        maxKey % 2 != 0 ? x = maxKey / 2 : x = maxKey / 2 - 1;

        for (int i = 0; i < x; i++)
            left->arr[i] = p->arr[i], left->n++;

        for (int i = 0; i <= x; i++)
            left->child[i] = p->child[i], left->childN++;

        for (int i = x + 1; i <= p->n; i++)
            right->arr[i - x - 1] = p->arr[i], right->n++;

        for (int i = x + 1; i <= p->n + 1; i++)
            right->child[i - x - 1] = p->child[i], right->childN++;

        p->arr[0] = p->arr[x], p->n = 0, p->leaf = false;
        p->childN = 2, p->child[0] = left, p->child[1] = right;

        if (flag)
            left->leaf = false, right->leaf = false;
        flag = 1;
    }

    void insertKey(BTreeNode *p, int key)
    {
        int index = p->n;
        for (int i = 0; i <= p->n; i++)
            if (key < p->arr[i])
            {
                index = i;
                break;
            }
        p->arr[index] > key ? index : index++;
        if (p->child[index]->leaf)
            sortNodeKeys(p->child[index], key);
    }

    int sortNodeKeys(BTreeNode *p, int key)
    {
        int index = p->n + 1;
        for (int i = 0; i <= p->n; i++)
            if (key < p->arr[i])
            {
                index = i;
                break;
            }
        for (int i = p->n; i >= index; i--)
            p->arr[i + 1] = p->arr[i];
        p->arr[index] = key, p->n++;
        return index;
    }

    BTreeNode *arrangeSplit(BTreeNode *p, int k = 0)
    {
        if (!p->leaf)
        {
            BTreeNode *node;
            for (int i = 0; i < p->childN; i++)
            {
                node = arrangeSplit(p->child[i]);
                if (node)
                {
                    int key = node->arr[0], keyIndex;
                    for (int i = 0; i < node->n; i++)
                        node->arr[i] = node->arr[i + 1];

                    node->n--;
                    keyIndex = sortNodeKeys(p, key);

                    for (int i = p->childN - 1; i >= keyIndex + 1; i--)
                        p->child[i + 1] = p->child[i];
                    p->child[keyIndex + 1] = node, p->childN++;
                }
            }
            if (p->n == maxKey)
                splitParent(p);
        }
        else if (p->leaf)
        {
            if (p->n == maxKey)
            {
                int x;
                maxKey % 2 != 0 ? x = maxKey / 2 : x = maxKey / 2 - 1;

                BTreeNode *ptr = new BTreeNode(maxKey);
                for (int i = x; i <= p->n; i++)
                    ptr->arr[i - x] = p->arr[i], ptr->n++;
                p->n = x - 1;
                return ptr;
            }
            else
                return NULL;
        }
        else
            return NULL;
        return NULL;
    }
    bool search(int key)
    {
        return search(key, root);
    }
    bool search(int key, BTreeNode *p)
    {
        if (!p->leaf)
        {
            for (int i = 0; i < p->childN; i++)
            {
                int index = p->n + 1;
                for (int j = 0; j <= p->n; j++)
                    if (p->arr[j] == key)
                        return true;
                for (int k = 0; k <= p->n; k++)
                    if (key < p->arr[k])
                    {
                        index = k;
                        break;
                    }
                return search(key, p->child[index]);
            }
        }
        else if (p->leaf)
        {
            for (int i = 0; i <= p->n; i++)
                if (p->arr[i] == key)
                    return true;
        }
        return false;
    }

    void display()
    {
        traverse(root);
        cout << endl;
    }
    void traverse(BTreeNode *p)
    {
        static int pl, lp;

        if (!p->leaf)
        {
            for (int i = 0; i < p->childN; i++)
                traverse(p->child[i]);
            cout << "PARENT " << pl++ << " ===> No. Key's : " << (p->n + 1) << endl;
            for (int i = 0; i <= p->n; i++)
                cout << p->arr[i] << " ";
            cout << endl;
        }
        else if (p->leaf)
        {
            cout << "leaf " << lp++ << " ---> No. Key's : " << (p->n + 1) << endl;
            for (int i = 0; i <= p->n; i++)
                cout << p->arr[i] << " ";
            cout << endl;
        }
        if (p == root)
            pl = 0, lp = 0;
    }
};

int main()
{
    BTree *b = new BTree;
    // b.insert(56);
    // b.insert(1);
    // b.insert(45);
    // b.insert(78);
    // b.insert(40);
    // b.insert(14);
    // b.insert(7);
    // b.insert(20);
    // b.insert(200);
    // b.insert(2);
    // b.insert(50);
    // b.insert(57);
    // b.insert(3);
    // b.insert(43);
    // b.insert(5);
    // b.insert(576);
    // b.display();

    int option, key;
    while (true)
    {
        cout << "Select any one : \n"
             << "1. Insert key\n"
             << "2.Search\n"
             << "3.Display\n"
             << "0.Exit\n";
        cin >> option;
        if (option == 1)
        {
            cout << "Enter key : ";
            cin >> key;
            b->insert(key);
        }
        else if (option == 2)
        {
            cout << "Enter key : ";
            cin >> key;
            cout << "Key " << key << " is " << (b->search(key) ? "Available" : "Unavailabe") << endl;
        }
        else if (option == 3)
            b->display();
        else if (!option)
            break;
    }
    delete b;
    return 0;
}
