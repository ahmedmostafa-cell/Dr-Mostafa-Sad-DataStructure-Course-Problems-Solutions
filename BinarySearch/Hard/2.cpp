#include<iostream>
#include<sstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<climits>
#include<algorithm>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node() :
		val(0), left(nullptr), right(nullptr) {
	}
	Node(int x) :
		val(x), left(nullptr), right(nullptr) {
	}
	Node(int x, Node* left, Node* right) :
		val(x), left(left), right(right) {
	}
};

class Solution {
public:

	pair<Node*, Node*> treeToDoublyListTraversal(Node* root) {
		if (!root)
			return { nullptr, nullptr };

		pair<Node*, Node*> left = treeToDoublyListTraversal(root->left);
		pair<Node*, Node*> right = treeToDoublyListTraversal(root->right);

		Node* first = root;	// if no left subtree, then root is the 1st
		Node* last = root;

		if (left.first) { // connect left last to current root
			left.second->right = root;
			root->left = left.second;
			first = left.first;
		}
		if (right.first) { // connect root to right first
			root->right = right.first;
			right.first->left = root;
			last = right.second;
		}
		return { first, last };
	}

	Node* treeToDoublyList(Node* root) {
		if (!root)
			return root;

		pair<Node*, Node*> dll = treeToDoublyListTraversal(root);
		// Make it circular
		dll.first->left = dll.second;
		dll.second->right = dll.first;

		return dll.first;
	}
};

int main() {

	return 0;
}

