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
	int maxSofar = 0;
	int maxDepth(TreeNode* root) 
	{
		if (!root)
			return 0;
		
		int l = maxDepth(root->left);
		int r = maxDepth(root->right);
		maxSofar = max(maxSofar, l + r);
		return 1 + max(r, l);
	}
	int diam(TreeNode* root) 
	{
		maxDepth(root);
		return maxSofar;
	}
	pair<int,int> diamm(TreeNode* root) 
	{
		pair<int, int> res = make_pair(0, 0);
		if (isLeaf(root))
			return res;
		pair<int, int> l = make_pair(0, 0);
		pair<int, int> r = make_pair(0, 0);
		if(root->left)
			l = diamm(root->left), res.first += 1 + l.second;
		if (root->right)
			r = diamm(root->right), res.first += 1 + r.second;
		res.first = max(res.first, max(l.first , r.first));
		res.second = 1 + max(l.second, r.second);


		return res;

	}
	
};

int main()
{
	BinaryTree tree(1);
	tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add({ 3, 6, 10 }, { 'R', 'R', 'L' });

	auto results = Solution().diamm(tree.root).first;


	cout << results;
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
