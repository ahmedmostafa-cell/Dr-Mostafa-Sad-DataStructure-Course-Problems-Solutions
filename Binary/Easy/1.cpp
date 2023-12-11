// ConsoleApplication17.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    bool isLeaf(TreeNode* node)
    {
        return node && !node->left && !node->right;
    }
  
   
};
class solution
{
public:
   int maxValue(TreeNode* current) 
   {
       if (!current)
           return 0;
       int maxy = max(maxValue(current->left), maxValue(current->right));
       return max(maxy, current->data);
   }

};
int main()
{
    BinaryTree tree(1);
    cout << solution().maxValue(tree.root) << "\n";

    tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    cout << solution().maxValue(tree.root) << "\n";

    tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    cout << solution().maxValue(tree.root) << "\n";

    tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    cout << solution().maxValue(tree.root) << "\n";

    tree.add({ 3, 6, 10 }, { 'R', 'R', 'L' });
    cout << solution().maxValue(tree.root) << "\n";
}

