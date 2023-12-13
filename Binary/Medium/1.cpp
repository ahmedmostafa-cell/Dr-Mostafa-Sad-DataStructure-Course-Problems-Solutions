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
	vector<vector<int>> zig(TreeNode* root) 
	{
		deque<TreeNode*> q;
		vector<vector<int>> result;
		q.push_back(root);
		bool f = true;
		while(!q.empty()) 
		{
			int s = q.size();
			vector<int> level;
			while(s--) 
			{
				TreeNode* current;
				if(f) 
				{
					current = q.front();;
					q.pop_front();
					if (current->left)
						q.push_back(current->left);
					if (current->right)
						q.push_back(current->right);
				}
				else 
				{
					current = q.back();;
					q.pop_back();
					if (current->right)
						q.push_front(current->right);
					if (current->left)
						q.push_front(current->left);
				}
				level.push_back(current->val);
				
			}
			f = !f;
			result.push_back(level);
		}
		return result;
	}
};
int main()
{
	BinaryTree tree(3);
	tree.add({ 9 }, { 'L' });
	tree.add({ 20, 7 }, { 'R', 'R' });
	tree.add({ 20, 15 }, { 'R', 'L' });

	auto results = Solution().zig(tree.root);

	for (auto row : results) {
		for (auto col : row)
			cout << col << " ";
		cout << "\n";
	}

	/*
	 BinaryTree tree(1);
	 tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	 tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	 tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
	 tree.add( { 3, 6, 10 }, { 'R', 'R', 'L' });

	 auto results = Solution().zigzagLevelOrder(tree.root);

	 for (auto row : results) {
	 for (auto col : row)
	 cout << col << " ";
	 cout << "\n";
	 }
	 */

	cout << "nbye\n";
	return 0;
}

