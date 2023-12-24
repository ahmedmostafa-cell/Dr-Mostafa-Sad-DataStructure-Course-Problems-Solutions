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


	bool is_bst(TreeNode* root)
	{
		if (root)
		{
			if (root->left && root->left->val > root->val || root->right && root->right->val < root->val)
				return false;

		}
		else
			return true;


		return is_bst(root->left) && is_bst(root->right);
	}
	int kth(TreeNode* root,int &k) 
	{
		if (k == 0)
			return -1;
		if(root->left) 
		{
			int res=kth(root->left, k);
			if (k == 0) 
			{
				return res;
				

			}
				

		}
		--k;
		if (k == 0)
			return root->val;
		
		if (root->right)
			kth(root->right, k);
	
		return -1;
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

	cout << endl;
	BinaryTree tree2(50);
	tree2.add({ 30, 10, 12 }, { 'L', 'L', 'R' });
	tree2.add({ 30, 40 }, { 'L', 'R' });
	tree2.add({ 70, 60, 55 }, { 'R', 'L', 'L' });
	tree2.add({ 70, 80, 90 }, { 'R', 'R', 'R' });
	cout << tree2.is_bst(tree2.root);
	cout << endl;
	int k = 5;
	cout << tree2.kth(tree2.root,k);
	return 0;
}

