// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val{ };
	TreeNode* left{ };
	TreeNode* right{ };
	TreeNode(int val) :
		val(val) {
	}
};

struct BinaryTree {
	TreeNode* root{ };
	BinaryTree(int root_value) :
		root(new TreeNode(root_value)) {
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		TreeNode* current = this->root;
		// iterate on the path, create all necessary TreeNodes
		for (int i = 0; i < (int)values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new TreeNode(values[i]);
				else
					assert(current->left->val == values[i]);
				current = current->left;
			}
			else {
				if (!current->right)
					current->right = new TreeNode(values[i]);
				else
					assert(current->right->val == values[i]);
				current = current->right;
			}
		}
	}
};

bool isLeaf(TreeNode* node) {
	return node && !node->left && !node->right;
}

class Solution {
public:
	bool isCompleteTree(TreeNode* root)
	{
		queue<TreeNode*> q;
		
		q.push(root);
		bool not_allowed = false;
		while (!q.empty())
		{
			int s = q.size();
			
				while (s--)
				{
					TreeNode* current;
				
						current = q.front();
						q.pop();
						if (current->left)
							if (!not_allowed)
								q.push(current->left);
							else
								return false;
						else
							not_allowed = true;

						
						if (current->right)
							if (!not_allowed)
								q.push(current->right);
							else
								return false;
						else
							not_allowed = true;
				
				

				}
			
			
		}
		return true;
	}
};
int main()
{
	BinaryTree tree(3);
	tree.add({ 9 }, { 'L' });
	tree.add({ 9 , 10 }, { 'L' , 'R' });
	tree.add({ 9 , 100 }, { 'L' , 'L' });
	tree.add({ 90 }, { 'R'  });

	

	auto results = Solution().isCompleteTree(tree.root);

	cout << results << endl;
	cout << "\nbye\n";
	return 0;
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
