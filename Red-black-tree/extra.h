#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    string data;
    Node *left, *right, *parent;
    string color;
    static Node *nil_leaf;
    Node(int k, string d)
    {
        key = k;
        data = d;
        left = right = parent = nil_leaf;
        // cout << "nil_leaf address " << nil_leaf << endl;
        color = "red";
    }
    Node(int k, string d, string color)
    {
        key = k;
        data = d;
        left = right = parent = NULL;
        this->color = color;
    }
};


Node *Node::nil_leaf = new Node(99999, "dummy", "black");


Node *left_rotate(Node *root, Node *parent)
{
    Node *y = parent->right;
    parent->right = y->left;
    if (y->left != NULL && y->left != Node::nil_leaf)
    {
        y->left->parent = parent;
    }
    y->parent = parent->parent;
    if (parent->parent == NULL || parent->parent == Node::nil_leaf)
    {
        root = y;
    }
    else if (parent == parent->parent->left)
    {
        parent->parent->left = y;
    }
    else
    {
        parent->parent->right = y;
    }
    y->left = parent;
    parent->parent = y;
    return root;
}
Node *right_rotate(Node *root, Node *parent)
{
    Node *y = parent->left;
    parent->left = y->right;
    if (y->right != NULL && y->right != Node::nil_leaf)
    {
        y->right->parent = parent;
    }
    y->parent = parent->parent;
    if (parent->parent == NULL || parent->parent == Node::nil_leaf)
    {
        root = y;
    }
    else if (parent == parent->parent->left)
    {
        parent->parent->left = y;
    }
    else
    {
        parent->parent->right = y;
    }
    y->right = parent;
    parent->parent = y;
    return root;
}

Node *transplant(Node *root, Node *parentnode, Node *child)
{

    if (parentnode->parent == NULL || parentnode->parent == Node::nil_leaf)
    {
        // cout << "NULL parent";
        root = child;
        // cout << "root " << root << endl;
    }
    else if (parentnode == parentnode->parent->left)
    {
        parentnode->parent->left = child;
    }
    else
    {
        parentnode->parent->right = child;
    }
    child->parent = parentnode->parent;
    return root;
}

Node *minimum(Node *deletenode)
{

    if (deletenode->left == Node::nil_leaf)
    {
        return deletenode;
    }
    while (deletenode->left != Node::nil_leaf)
    {
        deletenode = deletenode->left;
    }
    return deletenode;
}

Node *maximum(Node *deletenode)
{

    if (deletenode->right == Node::nil_leaf)
    {
        return deletenode;
    }
    while (deletenode->right != Node::nil_leaf)
    {
        deletenode = deletenode->right;
    }
    return deletenode;
}