#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct TreeNode {
	int val{ };
	TreeNode* left{ };
	TreeNode* right{ };
	TreeNode(int val) : val(val) { }
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

	void _print_inorder(TreeNode* current) {
		if (!current)
			return;
		_print_inorder(current->left);
		cout << current->val << " ";
		_print_inorder(current->right);
	}


	void print_inorder() {
		_print_inorder(root);
		cout << "\n";
	}

	bool _search(TreeNode* root, int target) {	// tail recursion
		if (!root)
			return false;

		if (target == root->val)
			return true;

		if (target < root->val)
			return _search(root->left, target);

		return _search(root->right, target);
	}

	bool search(int target) {
		return _search(root, target);
	}

	void _insert(TreeNode* root, int target) {
		if (target < root->val) {
			if (!root->left)
				root->left = new TreeNode(target);
			else
				_insert(root->left, target);
		}
		else if (target > root->val) {
			if (!root->right)
				root->right = new TreeNode(target);
			else
				_insert(root->right, target);
		} // else: exists already
	}

	void insert(int target) {
		if (!root)
			root = new TreeNode(target);
		else
			_insert(root, target);
	}


	bool is_bst(TreeNode* root, long long mn = LONG_MIN, long long mx = LONG_MAX)
	{
		bool status = root->val > mn && root->val < mx;
		if (!status)
			return false;
		bool left = !root->left || is_bst(root->left, mn, root->val);
		if (!left)
			return false;
		bool right = !root->right || is_bst(root->right, root->val, mx);
		return right;

	}
	TreeNode* lca(TreeNode* root , int x , int y) 
	{
		if (root->val > x && root->val > y)
			return lca(root->left, x, y);

		if (root->val < x && root->val < y)
			return lca(root->right, x, y);

		return root;
	}


};


int main() {
	BinaryTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	tree.print_inorder();
	cout << tree.is_bst(tree.root);


	BinaryTree tree2(50);
	tree2.add({ 30, 10, 12 }, { 'L', 'L', 'R' });
	tree2.add({ 30, 40 }, { 'L', 'R' });
	tree2.add({ 70, 60, 55 }, { 'R', 'L', 'L' });
	tree2.add({ 70, 80, 90 }, { 'R', 'R', 'R' });
	cout << tree2.is_bst(tree2.root);
	
	cout << endl;
	cout << tree2.lca(tree2.root,30,12)->val;
	return 0;
}

