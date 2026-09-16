#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class node
{
public:
    ll data;
    node *left;
    node *right;

    node(ll val)
    {
        data = val;
        left = right = NULL;
    }
};

class bst
{
public:
    node *root;
    bst()
    {
        root = NULL;
    }

    // insertion
    node *insertion(node *root, ll key)
    {
        if (!root)
            return new node(key);
        else if (root->data > key)
            root->left = insertion(root->left, key);
        else if (root->data < key)
            root->right = insertion(root->right, key);
        return root;
    }

    // find predecessor for use in deletion
    node *successor(node *root)
    {
        root = root->right;
        while (root->left)
            root = root->left;
        return root;
    }

    // deletion
    node *deletion(node *root, int key)
    {
        if (!root)
            return root;
        if (root->data > key)
            root->left = deletion(root->left, key);
        else if (root->data < key)
            root->right = deletion(root->right, key);
        else
        {
            if (!root->left || !root->right)
            {
                node *temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            else
            {
                node *temp = successor(root);
                root->data = temp->data;
                root->right = deletion(root->right, temp->data);
            }
        }
        return root;
    }

    int height(node *root)
    {
        if (!root)
            return -1;
        return (1 + max(height(root->left), height(root->right)));
    }
    int depth(node *root, ll key)
    {
        int dep = 0;
        while (root)
        {
            if(root->data == key)
            return dep;
            if (root->data > key)
                root = root->left;
            else if (root->data < key)
                root = root->right;
            dep++;
        }
        return -1;
    }
};