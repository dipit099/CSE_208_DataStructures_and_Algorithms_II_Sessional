/*max fibonacci heap*/
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key, data;
    Node *parent;
    Node *child;
    Node *left;
    Node *right;
    int degree;
    bool mark;
    Node(int key, int data)
    {
        this->key = key;
        this->data = data;
        this->parent = NULL;
        this->child = NULL;
        this->left = this;
        this->right = this;
        this->degree = 0;
        this->mark = false;
    }
};

Node *myarray[100000];

class Fibonacci_heap
{
public:
    Node *max_node;
    int node_count;
    // map<Node *, int> node_map;
};
Fibonacci_heap *make_heap(Fibonacci_heap *&heap)
{
    heap->max_node = NULL;
    heap->node_count = 0;
    for (int i = 0; i <= 10000; i++)
    {
        myarray[i] = NULL;
    }
    return heap;
}
void print(Fibonacci_heap *&heap)
{
    /*print root list*/
    Node *temp = heap->max_node;
    if (temp == NULL)
    {
        cout << "Heap is empty" << endl;
        return;
    }
    do
    {
        cout << "(" << temp->key << " " << temp->data << ")," << endl;
        temp = temp->right;
    } while (temp != heap->max_node);
}

void printFibonacciHeap(Node *&temp_max)
{
    if (temp_max == NULL)
    {
        cout << "Heap is empty" << endl;
        return;
    }
    Node *temp = temp_max;

    int count = 1;

    do
    {
        if (temp->parent == NULL)
        {
            cout << "Tree " << count << ": (" << temp->key << "," << temp->data << ")";
            count++;
            if (temp->child != NULL)
            {
                cout << " -> ";
            }
            else
            {
                cout << endl;
            }
        }

        if (temp->child != NULL)
        {

            if (temp->parent != NULL)
            {
                cout << "        (" << temp->key << "," << temp->data << ") -> ";
            }
            Node *temp1 = temp->child;
            do
            {
                // cout << "The key of the node is: " << temp1->key << " and the value of the node is: " << temp1->data << endl;
                if (temp1->right != temp->child)
                {
                    cout << "(" << temp1->key << "," << temp1->data << "),";
                }
                else
                {
                    cout << "(" << temp1->key << "," << temp1->data << ")";
                }

                temp1 = temp1->right;
            } while (temp1 != temp->child);
            cout << endl;
            printFibonacciHeap(temp->child);
        }
        temp = temp->right;
    } while (temp != temp_max);
}

void insert(Fibonacci_heap *&heap, int key, int value)
{
    Node *node = new Node(key, value);
    if (heap->max_node == NULL)
    {
        heap->max_node = node;
    }
    else
    {
        node->left = heap->max_node->left;
        node->right = heap->max_node;
        heap->max_node->left->right = node;
        heap->max_node->left = node;
        if (node->key > heap->max_node->key)
        {
            heap->max_node = node;
        }
    }
    heap->node_count++;
    // heap->node_map[node] = value;
    myarray[value] = node;
}
void link(Fibonacci_heap *&heap, Node *&temp, Node *&temp_max_node)
{
    (temp->left)->right = temp->right;
    (temp->right)->left = temp->left;
    if (temp_max_node->right == temp_max_node)
    {
        heap->max_node = temp_max_node;
    }
    temp->left = temp;
    temp->right = temp;
    temp->parent = temp_max_node;
    if (temp_max_node->child == NULL)
    {
        temp_max_node->child = temp;
    }
    temp->right = temp_max_node->child;
    temp->left = (temp_max_node->child)->left;
    (temp_max_node->child)->left->right = temp;
    temp_max_node->child->left = temp;
    if (temp->key > (temp_max_node->child)->key)
    {
        temp_max_node->child = temp;
    }
    temp_max_node->degree++;
    temp->mark = false;
    // cout << "linking\n";
    // cout << temp_max_node->key << " " << temp_max_node->data << " " << temp->key << " " << temp->data << endl;
    // cout << "temp-max-node-degree " << temp_max_node->degree << endl;
}

void consolidate(Fibonacci_heap *&heap)
{

    // int max_degree = log2(heap->node_count); /*1.618 ..length*/
    // vector<Node *> degree_table(max_degree + 1, NULL);/*plus 1*/
    Node *temp_max_node = heap->max_node;
    // cout << "temp_max_node " << temp_max_node->key << " " << temp_max_node->data << endl;

    int num_roots = 0;
    if (temp_max_node != NULL)
    {
        num_roots++;
        temp_max_node = temp_max_node->right;
        while (temp_max_node != heap->max_node)
        {
            num_roots++;
            temp_max_node = temp_max_node->right;
        }
    }
    // cout << "num_roots " << num_roots << endl;
    vector<Node *> degree_table(num_roots + 3, NULL);
    int max_degree = num_roots+2;
    temp_max_node = heap->max_node;
    // cout << "num_roots " << num_roots << endl;
    //  printFibonacciHeap(heap->max_node);
    while (num_roots > 0)
    {
        int degree = temp_max_node->degree;
        // cout << "in consolidate loop\n";
        // cout << temp_max_node->key << " " << temp_max_node->data << " " << degree << endl;

        Node *next = temp_max_node->right;
        while (degree_table[degree] != NULL)
        {
            Node *other = degree_table[degree];
            if (temp_max_node->key < other->key)
            {
                Node *temp = temp_max_node;
                temp_max_node = other;
                other = temp;
            }
            link(heap, other, temp_max_node);
            degree_table[degree] = NULL;
            degree++;
        }
        degree_table[degree] = temp_max_node;
        // temp_max_node->parent = NULL;
        temp_max_node = next;
        num_roots--;
    }

    heap->max_node = NULL;
    // cout << "creating rootlist new\n";



    for (int i = 0; i <= max_degree; i++) /*joining*/
    {
       
        
        if (degree_table[i] != NULL)
        {
        
            
            if (heap->max_node != NULL)
            {
//                 cout <<"maxnode"<< heap->max_node->key << endl;
//                  cout << "joining  "<<heap->max_node->key <<" &-> "<<degree_table[i]->key<<endl;
// cout << heap->max_node->left->key <<" "<<degree_table[i]->key<<endl;
                (heap->max_node->left)->right = degree_table[i];
               
                // degree_table[i]->left = heap->max_node->left; /*changeed  degree_table[i]->right->left = heap->max_node->left*/
                // cout << degree_table[i]->key << " " << heap->max_node->left->key << endl;
                degree_table[i]->left = heap->max_node->left;
               
//  cout << degree_table[i]->key << " " << heap->max_node->key << endl;
                degree_table[i]->right = heap->max_node;
                
                //  cout << heap->max_node->key <<" " << degree_table[i]->key << endl;
                heap->max_node->left = degree_table[i];
               


                if (degree_table[i]->key > heap->max_node->key)
                {
                    heap->max_node = degree_table[i];
                    
                }
                // cout << "left of maxnode\n";
                //  cout << heap->max_node->key <<" , "<< heap->max_node->left->key<<"," << heap->max_node->right->key << endl;
              
            }
            else
            {
                // cout << "max heap node added from degree table  "<<i <<" "<<degree_table[i]->key<<endl;
                heap->max_node = degree_table[i];
                heap->max_node->left= heap->max_node;
                    heap->max_node->right= heap->max_node;
            }
        }
    }
    // cout << "in consolidate\n";
    // cout << heap->max_node->key << " " << heap->max_node->data << endl;
}

Node *find_max(Fibonacci_heap *&heap)
{
    return heap->max_node;
}

void cut(Fibonacci_heap *&heap, Node *&node, Node *&parent);
void cascading_cut(Fibonacci_heap *&heap, Node *&node);
void extract_max(Fibonacci_heap *&heap)
{
    Node *temp_max_node = heap->max_node;
    if (temp_max_node != NULL)
    {
        Node *child = temp_max_node->child;
        Node *temp = child;
        if (temp != NULL)
        {
            do
            {
                Node *next = temp->right;
                (heap->max_node->left)->right = temp;
                temp->right = heap->max_node;
                temp->left = heap->max_node->left;
                heap->max_node->left = temp;
                temp->parent = NULL;
                temp = next;
            } while (temp != child);
        }
        (temp_max_node->left)->right = temp_max_node->right;
        (temp_max_node->right)->left = temp_max_node->left;
        if (temp_max_node == temp_max_node->right)
        {
            heap->max_node = NULL;
        }
        else
        {
            heap->max_node = temp_max_node->right;
            consolidate(heap);
        }
        heap->node_count--;
        myarray[temp_max_node->data] = NULL;
    }
}

void increase_key(Fibonacci_heap *&heap, int value, int new_key)
{
    // cout << "increase key\n";
    if (value < 0)
    {
        return;
    }

    Node *node = NULL;
    node = myarray[value];
    // cout << "node " << node << endl;

    if (node == NULL)
    {
        cout << "Node not found\n";
        return;
    }
    if (new_key < node->key)
    {
        return;
    }
    node->key = new_key; /*assign*/
    // cout << "new node new key and value " << new_key << " " << value << endl;
    Node *parent = node->parent;
    if (parent != NULL && node->key > parent->key)
    {
        cut(heap, node, parent);
        cascading_cut(heap, parent);
    }
    if (node->key > heap->max_node->key)
    {
        heap->max_node = node;
    }
}

void delete_value(Fibonacci_heap *&heap, int value)
{
    if (myarray[value] == NULL)
    {
        return;
    }
    increase_key(heap, value, INT_MAX);
    extract_max(heap);
}

Node *meld(Fibonacci_heap *&heap1, Fibonacci_heap *&heap2)
{
    if (heap1->max_node == NULL)
    {
        return heap2->max_node;
    }
    if (heap2->max_node == NULL)
    {
        return heap1->max_node;
    }
    Node *temp1 = heap1->max_node->right;
    Node *temp2 = heap2->max_node->left;
    heap1->max_node->right = heap2->max_node;
    heap2->max_node->left = heap1->max_node;
    temp1->left = temp2;
    temp2->right = temp1;

    if (heap1->max_node->key > heap2->max_node->key)
    {
        return heap1->max_node;
    }
    else
    {
        return heap2->max_node;
    }
}
bool empty(Fibonacci_heap *&heap)
{
    if (heap->max_node == NULL)
    {
        return true;
    }
    return false;
}
void cut(Fibonacci_heap *&heap, Node *&node, Node *&parent)
{
    if (node->right == node)
    {
        parent->child = NULL;
    }
    else
    {
        node->left->right = node->right;
        node->right->left = node->left;
        if (parent->child == node)
        {
            parent->child = node->right;
        }
    }
    parent->degree--;
    node->left = heap->max_node;
    node->right = heap->max_node->right;
    heap->max_node->right = node;
    node->right->left = node;
    node->parent = NULL;
    node->mark = false;
}
void cascading_cut(Fibonacci_heap *&heap, Node *&node)
{
    Node *parent = node->parent;
    if (parent != NULL)
    {
        if (node->mark == false)
        {
            node->mark = true;
        }
        else
        {
            cut(heap, node, parent);
            cascading_cut(heap, parent);
        }
    }
}
bool test()
{
    /*check if two files are identical*/
    ifstream file1("output.txt");
    ifstream file2("output1.txt");
    string line1, line2;
    while (getline(file1, line1) && getline(file2, line2))
    {
        if (line1 != line2)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    Fibonacci_heap *heap = new Fibonacci_heap();
    heap = make_heap(heap);
    while (n != 0)
    {

        if (n == 1)
        {
            int key, value;
            cin >> key >> value;
            insert(heap, key, value);
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 2)
        {
            if (empty(heap))
            {
                cout << "Heap is empty" << endl;
            }
            else
            {
                cout << "Heap is not empty" << endl;
            }
        }
        else if (n == 3)
        {
            // cout << "maxnode " << heap->max_node->key << " " << heap->max_node->data << endl;
            extract_max(heap);
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 4)
        {
            int value;
            cin >> value;
            delete_value(heap, value);
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 5)
        {

            Node *max_node = find_max(heap);
            if (max_node != NULL)
            {
                cout << "maxnode="
                     << "(" << max_node->key << "," << max_node->data << ")" << endl;
            }
            else
            {
                cout << "Heap is null so no maxnode" << endl;
            }
        }
        else if (n == 6)
        {
            int value, new_key;
            cin >> value >> new_key;
            increase_key(heap, value, new_key);
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 7)
        {
            heap = make_heap(heap);
        }
        else if (n == 8)
        {
            Fibonacci_heap *heap1= new Fibonacci_heap();
            heap1= make_heap(heap1);
            insert(heap1,90,12);
            meld(heap, heap1);
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 9)
        {
            printFibonacciHeap(heap->max_node);
        }
        else if (n == 10)
        {
            print(heap);
        }
        else
        {
            cout << "Invalid input\n";
            break;
        }
        cout << endl;
        cin >> n;
    }

    if (test())
    {
        cout << "passed\n";
    }
    else
    {
        cout << "not passed\n";
    }

    return 0;
}
