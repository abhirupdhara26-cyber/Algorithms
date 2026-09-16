#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class node
{
public:
    ll data;
    node *left;
    node *right;
    int height;

    node(ll val)
    {
        data = val;
        left = right = NULL;
        height = 0;
    }
};
class avl
{
public:
    node *root;
    avl()
    {
        root = NULL;
    }

    // height
    int height(node *root)
    {
        return root ? root->height : -1;
    }

    // update height
    void heightupdate(node *root)
    {
        root->height = (1 + max(height(root->left), height(root->right)));
    }
    // balance factor
    int getbalance(node *root)
    {
        return height(root->left) - height(root->right);
    }

    // right rotation
    node *balanceright(node *root)
    {
        node *y = root->left;
        node *x = y->right;

        root->left = x;
        y->right = root;

        heightupdate(root);
        heightupdate(y);

        return y;
    }

    // left rotation
    node *balanceleft(node *root)
    {
        node *y = root->right;
        node *x = y->left;

        root->right = x;
        y->left = root;

        heightupdate(root);
        heightupdate(y);

        return y;
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

        heightupdate(root);
        int bf = getbalance(root);

        if (bf > 1)
        {
            if (getbalance(root->left) >= 0)
                return balanceright(root);
            else
            {
                root->left = balanceleft(root->left);
                return balanceright(root);
            }
        }
        else if (bf < -1)
        {
            if (getbalance(root->right) <= 0)
                return balanceleft(root);
            else
            {
                root->right = balanceright(root->right);
                return balanceleft(root);
            }
        }
        return root;
    }

    // find succcessor for use in deletion
    node *successor(node *root)
    {
        root = root->right;
        while (root->left)
            root = root->left;
        return root;
    }

    // deletion
    node *deletion(node *root, ll key)
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

        heightupdate(root);
        int bf = getbalance(root);

        if (bf > 1)
        {
            if (getbalance(root->left) >= 0)
                return balanceright(root);
            else
            {
                root->left = balanceleft(root->left);
                return balanceright(root);
            }
        }
        else if (bf < -1)
        {
            if (getbalance(root->right) <= 0)
                return balanceleft(root);
            else
            {
                root->right = balanceright(root->right);
                return balanceleft(root);
            }
        }
        return root;
    }

    //preorder
    void preordertraversal(node *root)
    {
        if (!root)
            return;
        cout << root->data << " ";
        preordertraversal(root->left);
        preordertraversal(root->right);
    }
    //inorder
    void inordertraversal(node *root)
    {
        if (!root)
            return;
        inordertraversal(root->left);
        cout << root->data << " ";
        inordertraversal(root->right);
    }
    //postorder
    void postordertraversal(node *root)
    {
        if (!root)
            return;
        postordertraversal(root->left);
        postordertraversal(root->right);
        cout << root->data << " ";
    }
};

int main()
{
    avl tree;
    vector<ll> keys = {50, 25, 75, 10, 5, 90, 95, 20, 22};

    cout << "Inserting: ";
    for (ll k : keys)
    {
        cout << k << " ";
        tree.root = tree.insertion(tree.root, k);
    }
    cout << "\n\n";

    cout << "Inorder (should be sorted): ";
    tree.inordertraversal(tree.root);
    cout << "\n";

    cout << "Preorder (reveals shape):   ";
    tree.preordertraversal(tree.root);
    cout << "\n";

    cout << "Postorder:                  ";
    tree.postordertraversal(tree.root);
    cout << "\n\n";

    cout << "Deleting 5\n";
    tree.root = tree.deletion(tree.root, 5);
    cout << "Inorder:  ";
    tree.inordertraversal(tree.root);
    cout << "\nPreorder: ";
    tree.preordertraversal(tree.root);
    cout << "\n\n";

    cout << "Deleting 75\n";
    tree.root = tree.deletion(tree.root, 75);
    cout << "Inorder:  ";
    tree.inordertraversal(tree.root);
    cout << "\nPreorder: ";
    tree.preordertraversal(tree.root);
    cout << "\n";

    return 0;
}