// ConsoleApplication22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
struct TreeNode
{
    int data{};
    TreeNode* right{};
    TreeNode* left{};
    TreeNode(int data) : data(data) {};
};
struct BinaryTree
{
    TreeNode* root{};
    BinaryTree(int root_value) : root(new TreeNode(root_value)) {};

    void add(vector<int> values, vector<char> directions)
    {
        assert(values.size() == directions.size());
        TreeNode* curr = root;
        for (int i = 0;i < values.size();i++)
        {
            if (directions[i] == 'L')
            {
                if (!curr->left)
                    curr->left = new TreeNode(values[i]);
                else
                    assert(curr->left->data == values[i]);
                curr = curr->left;
            }
            else if (directions[i] == 'R')
            {
                if (!curr->right)
                    curr->right = new TreeNode(values[i]);
                else
                    assert(curr->right->data == values[i]);
                curr = curr->right;
            }

        }
    }
    void inorderPrint(TreeNode* root)
    {
        if (!root)
            return;
        inorderPrint(root->left);
        cout << root->data << " ";
        inorderPrint(root->right);
    }
    void inorder()
    {
        inorderPrint(root);
    }
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        return max(l, r) + 1;
    }
    bool isLeaf(TreeNode* node)
    {
        return node && !node->left && !node->right;
    }
    bool isPerfect(TreeNode* current, int h)
    {
        if (isLeaf(current))
            return h == 0;
        if (!current->left && current->right || current->left && !current->right)
            return false;
        return isPerfect(current->left, h - 1) && isPerfect(current->right, h - 1);
    }
    bool isper()
    {
        return isPerfect(root, maxDepth(root) - 1);
    }



};
bool isLeaf(TreeNode* node)
{
    return node && !node->left && !node->right;
}


int main()
{
    BinaryTree tree(1);

  

    tree.add({ 2 }, { 'L' });


    cout << tree.isper() << endl;

    cout << "bye";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
