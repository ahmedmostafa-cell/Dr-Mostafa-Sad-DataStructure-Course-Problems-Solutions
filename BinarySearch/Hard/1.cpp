#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
	int val{ };
	TreeNode* left{ };
	TreeNode* right{ };
	TreeNode(int val) :
		val(val) {
	}
};

class Solution {
public:
	TreeNode* bstFromPreorder(vector<int>& preorder) {
		int i = 0;
		return bstFromPreorder(preorder, i, 0, 1001);
	}

	TreeNode* bstFromPreorder(vector<int>& preorder, int& i, int mn, int mx) {
		int data = preorder[i];

		// Simply if next node are my left, they must respect my min/max range
		TreeNode* root = new TreeNode(data);

		// Compute the next range of left/right nodes
		i += 1;
		if (next_between(preorder, i, mn, data))
			root->left = bstFromPreorder(preorder, i, mn, data);

		// Now: left subtree has been consumed if any
		if (next_between(preorder, i, data, mx))
			root->right = bstFromPreorder(preorder, i, data, mx);

		return root;
	}

	// Check if the next element in the preorder is in the range
	bool next_between(vector<int>& preorder, int i, int min, int max) {
		return i < preorder.size() && min < preorder[i] && preorder[i] < max;
	}
};

int main() {

	return 0;
}

