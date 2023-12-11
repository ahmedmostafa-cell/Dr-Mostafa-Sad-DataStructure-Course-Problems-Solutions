// ConsoleApplication21.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
bool isLeaf(TreeNode* node)
{
    return node && !node->left && !node->right;
}
class solution
{
public:
  int findDepth(TreeNode* current , int x , int currDepth=0) 
  {
      if (!current)
          return 0;
      if (current->data == x)
          return currDepth;
      int l = findDepth(current->left, x, currDepth + 1);
      if (l)
          return l;
      return findDepth(current->right, x, currDepth + 1);
  }
  TreeNode* findParent(TreeNode* current, int x, TreeNode* p =nullptr)
  {
      if (!current)
          return nullptr;
      if (current->data == x)
          return p;
      TreeNode* l = findParent(current->left, x, current);
      if (l)
          return l;
      return findParent(current->right, x, current);
  }
  bool isCousin(TreeNode* current , int x , int y) 
  {
      if (findDepth(current, x) != findDepth(current, y))
          return false;
      if (findParent(current, x) == findParent(current, y))
          return false;
      return true;
  }



};

int main()
{
    BinaryTree tree(1);
    tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    tree.add({ 3, 6, 10 }, { 'R', 'R', 'L' });

    cout << solution().isCousin(tree.root, 7, 9) << "\n";	// 0
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
