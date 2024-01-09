#include<vector>
#include<queue>
#include<iostream>
#include<cassert>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left{ };
	BinaryTree* right{ };

public:

	BinaryTree(int data) :
		data(data) {
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int)values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			}
			else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}
	////////////////////////////////////////////

	void level_order_traversal() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			while (sz--) {
				BinaryTree* cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			cout << "\n";
		}
	}
	void level_order_traversal_sorted()
	{
		priority_queue<pair<int,BinaryTree*>>nodes_queue[2];
		int flag = 0;
		nodes_queue[flag].push(make_pair(data,this));

		while (!nodes_queue[flag].empty()) {
			int sz = nodes_queue[flag].size();

			while (sz--) {
				BinaryTree* cur = nodes_queue[flag].top().second;
				nodes_queue[flag].pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue[!flag].push(make_pair(cur->left->data,cur->left));
				if (cur->right)
					nodes_queue[!flag].push(make_pair(cur->right->data,cur->right));
			}
			cout << "\n";
			flag = !flag;
		}
	}

};
int main()
{
	BinaryTree tree(1);

	tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add({ 3, 6, 15 }, { 'R', 'R', 'L' });

	tree.add({ 2, 5, 13 }, { 'L', 'R', 'L' });
	tree.add({ 3, 6, 12 }, { 'R', 'R', 'R' });
	tree.add({ 3, 14, 15 }, { 'R', 'L', 'L' });
	tree.add({ 3, 14, 16 }, { 'R', 'L', 'R' });

	tree.level_order_traversal();
	tree.level_order_traversal_sorted();
	
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
