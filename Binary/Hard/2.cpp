// https://leetcode.com/problems/flip-equivalent-binary-trees

#include <iostream>
#include <sstream>	// ostringstream
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

string toStr(int n) {
	// Convert integer to string
	ostringstream oss;
	oss << n;
	return oss.str();
}

struct TreeNode {		// don't copy for leetcode
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
class Solution {
public:
	string parenthise(TreeNode* root , bool c) 
	{
		if (!root)
			return "()";
		string repr = "(" + toStr(root->val);
		if(c) 
		{
			if (root->left)
				repr += parenthise(root->left, c);
			else
				repr += "()";
			if (root->right)
				repr += parenthise(root->right, c);
			else
				repr += "()";
		}
		else 
		{
			if (root->right)
				repr += parenthise(root->right, c);
			else
				repr += "()";
			if (root->left)
				repr += parenthise(root->left, c);
			else
				repr += "()";
		}
		

		repr += ")";
		return repr;

			
	}


	string parenthise_canonical(TreeNode* root)
	{
		
		if (!root)
			return "()";
		vector<string>v;
		string repr = "(" + toStr(root->val);
		
			if (root->left) 
			
				v.push_back(parenthise_canonical(root->left));
			else
				v.push_back(repr += "()");
			if (root->right)
				v.push_back(parenthise_canonical(root->right));
			else
				v.push_back(repr += "()");
		
			

			sort(v.begin(), v.end());
			for(int i=0;i<(int)v.size();i++) 
			{
				repr += v[i];
			}
		
		
		return repr;


	}

	bool is_flip(TreeNode* root) 
	{
		if (!root)
			return false;
		
		return parenthise_canonical(root->left) == parenthise_canonical(root->right);
	}

	bool isSym(TreeNode* root) 
	{
		if (!root)
			return false;
		return is_sym(root->left, root->right);
	}
	bool isSym2(TreeNode* root)
	{
		if (!root)
			return false;
		return is_sym2(root->left, root->right);
	}
	bool is_sym(TreeNode* first , TreeNode* second) 
	{
		if (!first && !second)
			return true;
		if (!first && second || first && !second || first->val!=second->val)
			return false;
		return is_sym(first->left, second->right) && is_sym(first->right, second->left);
	}
	bool is_sym2(TreeNode* first, TreeNode* second)
	{
		if (!first && !second)
			return true;
		if (!first && second || first && !second || parenthise(first,true) != parenthise(second, false))
			return false;
		return is_sym2(first->left, second->right) && is_sym(first->right, second->left);
	}


};

int main()
{
	BinaryTree tree(1);
	tree.add({ 2, 3}, { 'L', 'L' });
	tree.add({ 2,4 }, { 'L', 'R' });
	tree.add({ 2, 3 }, { 'R', 'R' });
	tree.add({ 2,4 }, { 'R', 'L' });

	cout << Solution().is_flip(tree.root) << "\n";
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
