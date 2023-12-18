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
	string parenthise(TreeNode* root, vector<string>&allrep)
	{
		if (!root)
			return "()";
		string repr = "(" + toStr(root->val);
		
			if (root->left)
				repr += parenthise(root->left, allrep);
			else
				repr += "()";
			if (root->right)
				repr += parenthise(root->right, allrep);
			else
				repr += "()";
		


		repr += ")";
		if (root->left || root->right)
			allrep.push_back(repr);
		return repr;


	}
	void print_duplicate(TreeNode* root) 
	{
		vector<string>allrep;
		parenthise(root, allrep);
		sort(allrep.begin(), allrep.end());
		for(int i=0;i<(int)allrep.size();) 
		{
			int j = i + 1;
			while (j < (int)allrep.size()&&allrep[i] == allrep[j])
				j++;
			if (j > i + 1)
				cout << allrep[i] << endl;
			i = j;
			
		}

	}

	string parenthise_canonical(TreeNode* root)
	{

		if (!root)
			return "()";
		string repr = "(" + toStr(root->val);
		vector<string>v;
		if (root->left)
			v.push_back(parenthise_canonical(root->left));
		else
			return "()";
		if (root->right)
			v.push_back(parenthise_canonical(root->right));
		else
			return "()";
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size();i++) 
		{
			repr += v[i];
		}
		repr += ")";
		return repr;


	}

	


};
int main()
{
	BinaryTree tree(1);
	/*
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 9 }, { 'L', 'L', 'R' });
	tree.add( { 2, 5, 10 }, { 'L', 'R', 'L' });
	tree.add( { 2, 5, 11 }, { 'L', 'R', 'R' });

	tree.add( { 3, 6, 12 }, { 'R', 'L', 'L' });
	tree.add( { 3, 6, 13 }, { 'R', 'L', 'R' });
	tree.add( { 3, 7, 14 }, { 'R', 'R', 'L' });
	tree.add( { 3, 7, 15 }, { 'R', 'R', 'R' });
	tree.add( { 3, 7, 15, 16 }, { 'R', 'R', 'R', 'R' });

	Solution().print_duplicate_subtrees(tree.root);
	*/

	tree.add({ 2, 3 }, { 'L', 'L' });
	tree.add({ 4, 5, 6, 8, 9 }, { 'R', 'R', 'R', 'R', 'R' });
	tree.add({ 4, 2, 3 }, { 'R', 'L', 'L' });
	tree.add({ 4, 5, 6, 7 }, { 'R', 'R', 'L', 'L' });
	tree.add({ 4, 5, 6, 8, 9 }, { 'R', 'R', 'L', 'R', 'R' });
	tree.add({ 4, 5, 6, 7 }, { 'R', 'R', 'R', 'L' });

	// (2(3()())())
	// (6(7()())(8()(9()())))
	// (8()(9()()))

	Solution().print_duplicate(tree.root);
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
