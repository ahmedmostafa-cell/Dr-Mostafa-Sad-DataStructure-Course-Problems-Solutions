// https://leetcode.com/problems/recover-binary-search-tree/discuss/781762/C%2B%2B-Straightforward-DFS-solution


// It looks simple, but tricky for swapped nodes when one is ancestor to another
// Feel free to ignore it
// I am just providing for whoever have interest.


#include<iostream>
#include<sstream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<unordered_set>
#include<climits>
#include<algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() :
		val(0), left(nullptr), right(nullptr) {
	}
	TreeNode(int x) :
		val(x), left(nullptr), right(nullptr) {
	}
	TreeNode(int x, TreeNode* left, TreeNode* right) :
		val(x), left(left), right(right) {
	}
};


class Solution {
	TreeNode* cur_mn = nullptr, * cur_mx = nullptr;

	void update(TreeNode* mn, TreeNode* mx) {
		if (!cur_mn || mn < cur_mn)
			cur_mn = mn;
		if (!cur_mx || mx > cur_mx)
			cur_mx = mx;
	
	}
	void dfs(TreeNode* root, TreeNode* mn = nullptr, TreeNode* mx = nullptr) {
		if (!root)
			return;
		if (mn && mn->val > root->val)
			update(root, mn);
		if (mx && mx->val < root->val)
			update(mx, root);
		dfs(root->left, mn, root);
		dfs(root->right, root, mx);
		
	}

public:
	void recoverTree(TreeNode* root) {
		dfs(root);

		cout << cur_mn->val << " " << cur_mx->val;
		swap(cur_mn->val, cur_mx->val);
	}
};

int main() {
	TreeNode* n90 = new TreeNode(90);
	TreeNode* n60 = new TreeNode(60);
	TreeNode* n80 = new TreeNode(80);
	TreeNode* n50 = new TreeNode(50);
	TreeNode* n65 = new TreeNode(65);

	n90->left = n60;
	n60->right = n80;
	n80->left = n50;
	n50->right = n65;

	Solution s;
	s.recoverTree(n60);

	return 0;
}



int main1() {
	TreeNode* n50 = new TreeNode(50);
	TreeNode* n40 = new TreeNode(40);
	TreeNode* n30 = new TreeNode(30);
	TreeNode* n20 = new TreeNode(20);
	TreeNode* n35 = new TreeNode(35);
	TreeNode* n45 = new TreeNode(45);
	TreeNode* n70 = new TreeNode(70);

	n50->left = n20;
	n50->right = n70;

	n20->left = n30;
	n20->right = n45;

	n30->left = n40;
	n30->right = n35;

	Solution s;
	s.recoverTree(n50);

	return 0;
}
