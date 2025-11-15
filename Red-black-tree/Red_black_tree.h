#include "color.hpp"
#include "extra.h"
#include <bits/stdc++.h>
using namespace std;

class Red_black_tree
{

public:
    Node *root;
    int size;
    Node *dummy = Node::nil_leaf;
    Red_black_tree()
    {
        root = NULL;
        size = 0;
    }

    bool empty()
    {
        if (size == 0)
        {
            return true;
        }
        return false;
    }
    bool find(int key)
    {
        Node *temproot = root;
        while (temproot != NULL)
        {
            if (temproot->key == key)
            {
                return true;
            }
            else if (key < temproot->key)
            {
                temproot = temproot->left;
            }
            else
            {
                temproot = temproot->right;
            }
        }
        return false;
    }
    int length()
    {
        return size;
    }
    bool clear()
    {
        if (root != NULL)
        {
            // root = NULL;
            size = 0;
            postorder(root);
            root = NULL;
            return true;
        }
        else
        {
            return false;
        }
    }
    void postorder(Node *temproot)
    {
        if (temproot == NULL || temproot == dummy)
        {
            return;
        }
        if (temproot->left != NULL && temproot->left != dummy)
        {
            postorder(temproot->left);
        }
        if (temproot->right != NULL && temproot->right != dummy)
        {
            postorder(temproot->right);
        }

        delete temproot;
    }

    void insert(int key, string data)
    {
        // cout << "inserting " << key << endl;
        Node *newnode = new Node(key, data);

        Node *temproot = root;
        Node *curr = NULL;
        // cout << "dummy " << dummy << endl;
        while (temproot != dummy && temproot != NULL)
        {
            curr = temproot;
            if (key < temproot->key)
            {
                temproot = temproot->left;
            }
            else
            {
                temproot = temproot->right;
            }
        }
        // cout << "curr " << curr << endl;
        newnode->parent = curr;
        if (curr == NULL || curr == dummy)
        {
            root = newnode;
            // cout << "root " << root << endl;
        }
        else if (newnode->key < curr->key)
        {
            curr->left = newnode;
        }
        else if (newnode->key > curr->key)
        {
            curr->right = newnode;
        }
        else
        {
            curr->data = data;
            return;
        }
        /*insert fixup*/
        if (newnode->parent == dummy || newnode->parent == NULL)
        {
            newnode->color = "black";
        }
        else if (newnode->parent->color == "black")
        {
            /*do nothing*/
        }
        else
        {
            insert_fixup(newnode);
        }
        size++;
        // cout << "inserted " << key << endl;

        return;
    }
    void insert_fixup(Node *newnode)
    {
        /*parent is red */

        while (newnode->parent != NULL && newnode->parent != dummy && newnode->parent->color == "red")
        {

            if (newnode->parent == newnode->parent->parent->left)
            {

                Node *rightsibling = newnode->parent->parent->right;
                if (rightsibling != NULL && rightsibling != dummy && rightsibling->color == "red")
                {
                    newnode->parent->color = "black";
                    rightsibling->color = "black";
                    newnode->parent->parent->color = "red";
                    newnode = newnode->parent->parent;
                }
                else
                {
                    if (newnode == newnode->parent->right)
                    {
                        newnode = newnode->parent;
                        root = left_rotate(root, newnode);
                    }
                    newnode->parent->color = "black";
                    newnode->parent->parent->color = "red";
                    root = right_rotate(root, newnode->parent->parent);
                }
            }
            else
            {
                Node *leftsibling = newnode->parent->parent->left;
                if (leftsibling != NULL && leftsibling != dummy && leftsibling->color == "red")
                {
                    newnode->parent->color = "black";
                    leftsibling->color = "black";
                    newnode->parent->parent->color = "red";
                    newnode = newnode->parent->parent;
                }
                else
                {
                    if (newnode == newnode->parent->left)
                    {
                        newnode = newnode->parent;
                        root = right_rotate(root, newnode);
                    }
                    newnode->parent->color = "black";
                    newnode->parent->parent->color = "red";
                    root = left_rotate(root, newnode->parent->parent);
                }
            }
        }
        root->color = "black";
    }

    bool erase(int key)
    {

        Node *z = root;
        while (z != NULL)
        {
            if (z->key == key)
            {
                break;
            }
            else if (key < z->key)
            {
                z = z->left;
            }
            else
            {
                z = z->right;
            }
        }
        if (z == NULL)
        {
            // cout << key << " not found\n";
            return false;
        }
        string originalcolor = "";

        Node *y = z;
        // cout << z->parent << endl;
        Node *x = NULL;

        // cout << "z found\n";
        originalcolor = z->color;

        if (z->left == dummy)
        {
            // cout << "left\n";
            x = z->right;                         /*x=x*/
            root = transplant(root, z, z->right); /*z holo parent left or right child*/
        }
        else if (z->right == dummy)
        {
            // cout << "right\n";
            x = z->left;
            root = transplant(root, z, z->left);
        }

        else
        {
            // cout << "checking\n";
            y = maximum(z->left);
            originalcolor = y->color;
            x = y->left;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                root = transplant(root, y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            root = transplant(root, z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }

        if (originalcolor == "black")
        {

            // cout << x->parent << endl;
            // cout << x << endl;
            // cout << root << endl;
            // cout << x->parent->left << endl;
            // cout << "erasefixup\n";
            erase_fixup(x);
        }
        delete z;
        size--;
        return true;
    }
    void erase_fixup(Node *x) /*x = x*/
    {
        // cout << "inside erasefixup\n";
        // cout << x << " " << root << " " << x->color << endl;
        while (x != root && x->color == "black")
        {
            // cout << "inside erasefixup2\n";
            Node *w = NULL;
            if (x == x->parent->left)
            {
                // cout << "part1";
                w = x->parent->right; /*w=w*/
                if (w->color == "red")
                {
                    w->color = "black";
                    x->parent->color = "red";

                    root = left_rotate(root, x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == "black" && w->right->color == "black")
                {
                    // cout << "part2";
                    w->color = "red";
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == "black")
                    {
                        w->left->color = "black";
                        w->color = "red";
                        root = right_rotate(root, w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->right->color = "black";
                    root = left_rotate(root, x->parent);
                    x = root;
                }
            }
            else
            {
                // cout << "part2";
                Node *w = x->parent->left;
                if (w->color == "red")
                {
                    w->color = "black";
                    x->parent->color = "red";
                    root = right_rotate(root, x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == "black" && w->left->color == "black")
                {
                    w->color = "red";
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == "black")
                    {
                        w->right->color = "black";
                        w->color = "red";
                        root = left_rotate(root, w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->left->color = "black";
                    root = right_rotate(root, x->parent);
                    x = root;
                }
            }
        }
        x->color = "black";
        // cout << "erasefixupdone";
    }
    void inorder(Node *temproot)
    {
        if (temproot == NULL || temproot == dummy)
        {
            return;
        }
        inorder(temproot->left);
        cout << temproot->key << " => " << temproot->data << endl;
        inorder(temproot->right);
    }
    void iteration(Node *temproot)
    {
        // cout << "\niteration" << endl;
        // cout << temproot << endl;
        // cout << dummy << endl;
        if (temproot == dummy || temproot == NULL)
        {
            // cout << "dummy node\n";
            return;
        }

        if (temproot == root)
        {
            cout << temproot->key << "_" << temproot->data;
        }
        else
        {
            if (temproot == temproot->parent->left)
            {
                if (temproot->color == "red")
                {
                    cout << "(" << dye::red(temproot->key) << "_" << dye::red(temproot->data);
                }
                else
                {
                    cout << "(" << temproot->key << "_" << temproot->data;
                }
            }
            else
            {
                if (temproot->parent->left != NULL && temproot->parent->left != dummy)
                {
                    if (temproot->color == "red")
                    {
                        cout << "," << dye::red(temproot->key) << "_" << dye::red(temproot->data);
                    }
                    else
                    {
                        cout << "," << temproot->key << "_" << temproot->data;
                    }
                }
                else
                {
                    if (temproot->color == "red")
                    {
                        cout << "(," << dye::red(temproot->key) << "_" << dye::red(temproot->data);
                    }
                    else
                    {
                        cout << "(," << temproot->key << "_" << temproot->data;
                    }
                }
            }
        }
        iteration(temproot->left);
        iteration(temproot->right);
        if (temproot->left != dummy && temproot->right != dummy)
        {
            cout << ")";
        }
        else if (temproot->left != dummy && temproot->right == dummy)
        {
            cout << ",)";
        }
        else if (temproot->left == dummy && temproot->right != dummy)
        {
            cout << ")";
        }
        // cout << "closing" << endl;
    }
};