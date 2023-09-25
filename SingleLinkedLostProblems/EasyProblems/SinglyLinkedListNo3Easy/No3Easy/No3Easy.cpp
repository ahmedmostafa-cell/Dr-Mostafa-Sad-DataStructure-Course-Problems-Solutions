
#include<iostream>
#include<cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;
struct Node
{
	int data{ 0 };
	Node* Next{ nullptr };
	Node(int data) : data(data) {};
	~Node()
	{
		cout << "Destroy value: " << data << " at address " << this << "\n";
	};
};
class Linked_List
{
private:
	Node* Head{ nullptr };
	Node* Tail{ nullptr };
	int length{ 0 };
	vector<Node*> debug_data;
	void debug_add_node(Node* node)
	{
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node)
	{
		auto it = find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);

	}
public:
	void print()
	{
		for (Node* curr = Head; curr; curr = curr->Next)
		{
			cout << curr->data << " ";
		}
		cout << "\n";
	}
	Node* get_head()
	{
		return Head;
	}
	void insert_end(int data)
	{
		Node* node = new Node(data);
		add_node(node);
		if (!Head)
		{
			Head = Tail = node;
		}
		else
		{
			Tail->Next = node;
			Tail = node;
		}

	}
	void add_node(Node* node)
	{
		debug_add_node(node);
		length++;

	}
	void print_by_parameter(Node* node)
	{
		while (!node)
		{
			cout << node->data << " ";
			node = node->Next;
		}
		cout << "\n";
	}
	void get_length()
	{
		cout << length << endl;
	}
	void print_recursive(Node* node)
	{
		if (node)
		{
			cout << node->data << " ";
			print_recursive(node->Next);
		}
		cout << "\n";
	}
	void print_recursive_reverse(Node* node)
	{
		if (node)
		{
			print_recursive_reverse(node->Next);
			cout << node->data << " ";

		}
		cout << "\n";
	}
	Node* get_nth(int n)
	{
		int idx = 1;
		for (Node* curr = Head; curr; curr = curr->Next, idx++)
		{
			if (idx == n)
				return curr;
		}
		return nullptr;

	}
	int search(int data)
	{
		int idx = 0;
		for (Node* curr = Head; curr; curr = curr->Next, idx++)
		{
			if (curr->data == data)
				return idx;
		}
		return -1;

	}
	int improved_Search(int val)
	{
		int idx = 0;
		Node* prev{ nullptr };
		for (Node* curr = Head; curr; curr = curr->Next, idx++)
		{
			if (curr->data == val)
			{
				if (!prev)
				{
					return 0;
				}
				else
				{
					swap(curr->data, prev->data);
					return idx - 1;
				}
				prev = curr;

			}

		}
		return -1;

	}
	// Below 2 deletes prevent copy and assign to avoid this mistake
	Linked_List() {
	}
	~Linked_List()
	{
		while (Head)
		{
			Node* temp = Head->Next;
			delete_node(Head);
			Head = temp;

		}

	};
	Linked_List(const Linked_List&) = delete;
	Linked_List& operator=(const Linked_List& another) = delete;
	void debug_print_address()
	{
		for (Node* cur = Head; cur; cur = cur->Next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}
	void debug_print_node(Node* node, bool is_seperate = false)
	{
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->Next == nullptr)
			cout << "X ";
		else
			cout << node->Next->data << " ";

		if (node == Head)
			cout << "head\n";
		else if (node == Tail)
			cout << "tail\n";
		else
			cout << "\n";

	}
	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = Head; cur; cur = cur->Next) {
			oss << cur->data;
			if (cur->Next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(Head == nullptr);
			assert(Tail == nullptr);
			return;
		}

		assert(Head != nullptr);
		assert(Tail != nullptr);
		assert(Tail->Next == nullptr);

		if (length == 1)
			assert(Head == Tail);
		else {
			assert(Head != Tail);

			if (length == 2)
				assert(Head->Next == Tail);
			else if (length == 3) {
				assert(Head->Next);
				assert(Head->Next->Next == Tail);
			}
		}
		int len = 0;
		Node* prev = nullptr;
		for (Node* cur = Head; cur; prev = cur, cur = cur->Next, len++)
			assert(len < 10000);	// Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == Tail);	// last node is tail
	}

	////////////////////////////////////////////////////////////

	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void delete_first()
	{
		if (Head)
		{
			Node* temp = Head;
			Head = Head->Next;
			delete_node(temp);
			if (length == 0)
				Tail = nullptr;

			debug_verify_data_integrity();
		}
	}

	void delete_last()
	{
		if (length <= 1)
		{
			delete_first();
			return;
		}
		Node* prev = get_nth(length - 1);
		delete_node(Tail);
		Tail = prev;
		Tail->Next = nullptr;
		debug_verify_data_integrity();
	}


	void delete_nth_node(int n)
	{
		Node* node = get_nth(n);
		Node* prev_node = get_nth(n - 1);
		if (n < 1 || n > length)
			cout << "Error. No such nth node\n";
		else if (node == Head)
			delete_first();
		else if (node == Tail)
			delete_last();
		else
		{
			prev_node->Next = node->Next;
			delete_node(node);
		}
		debug_verify_data_integrity();
	}
	void insert_front(int data)
	{
		Node* node = new Node(data);
		add_node(node);
		if (!Head)
		{
			Head = Tail = node;
		}
		else
		{
			node->Next = Head;
			Head = node;
		}
		debug_verify_data_integrity();

	}
	void delete_front()
	{
		if(Head) 
		{
			if(length==1) 
			{
				delete_node(Head);
				Head = Tail = nullptr;
			}
			else 
			{
				Node* node = Head->Next;
				delete_node(Head);
				Head = node;
			}
			debug_verify_data_integrity();
		}
	}

};
int main()
{
	Linked_List l;
	l.insert_end(10);
	l.insert_end(20);
	l.insert_end(30);
	l.insert_front(5);
	l.print();
	return 0;
}