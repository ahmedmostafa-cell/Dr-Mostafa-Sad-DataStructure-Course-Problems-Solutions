#include<iostream>
#include<cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;
struct Node
{
	int data;
	Node* next{ nullptr };
	Node(int data) : data(data) {};
	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};
class Linked_List
{
private:
	Node* Head{ nullptr };
	Node* Tail{ nullptr };
	int length{ 0 };
	vector<Node*> debug_data;	// add/remove nodes you use
	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {

		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}
public:
	void print()
	{
		for (Node* curr = Head; curr; curr = curr->next)
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
		if (Head == nullptr)
		{
			Head = Tail = node;
		}
		else
		{

			Tail->next = node;
			Tail = node;
		}

		//length++;


	}
	void print_by_parameter(Node* node)
	{
		while (node)
		{
			cout << node->data << " ";
			node = node->next;

		}
		cout << "\n";
	}
	void get_length()
	{
		cout << length << endl;
	}
	void print_recursive(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data << " ";
			print_recursive(node->next);
		}

	}
	void print_recursive_reverse(Node* node)
	{
		if (node == nullptr)
		{
			cout << "\n";

		}
		else
		{
			print_recursive_reverse(node->next);
			cout << node->data << " ";
		}


	}
	Node* get_nth(int n)
	{
		int idx = 1;
		for (Node* curr = Head; curr; curr = curr->next, idx++)
		{
			if (idx == n)
				return curr;

		}
		return nullptr;

	}
	int search(int data)
	{
		int idx = 0;
		for (Node* curr = Head; curr; curr = curr->next, idx++)
		{
			if (curr->data == data)
				return idx;

		}
		return -1;
	}
	int improved_Search(int val)
	{
		Node* prev = nullptr;
		int idx = 0;
		for (Node* curr = Head; curr; curr = curr->next, idx++)
		{

			if (curr->data == val)
			{
				if (!prev)
					return 0;

				swap(prev->data, curr->data);
				return idx - 1;
			}
			prev = curr;


		}
		return -1;

	}
	// Below 2 deletes prevent copy and assign to avoid this mistake
	Linked_List() {
	}
	~Linked_List() {};
	Linked_List(const Linked_List&) = delete;
	Linked_List& operator=(const Linked_List& another) = delete;
	void debug_print_address() {
		for (Node* cur = Head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}
	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == Head)
			cout << "head\n";
		else if (node == Tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}
	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = Head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
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
		assert(Tail->next == nullptr);

		if (length == 1)
			assert(Head == Tail);
		else {
			assert(Head != Tail);

			if (length == 2)
				assert(Head->next == Tail);
			else if (length == 3) {
				assert(Head->next);
				assert(Head->next->next == Tail);
			}
		}
		int len = 0;
		Node* prev = nullptr;
		for (Node* cur = Head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == Tail);	// last node is tail
	}
	////////////////////////////////////////////////////////////
	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}
	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}
	void delete_first()
	{

		if (Head)
		{
			Node* cur = Head;
			Head = Head->next;
			delete_node(cur);
			if (!Head)
			{
				Tail = nullptr;
			}
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
		Tail->next = nullptr;

		debug_verify_data_integrity();
	}
	void delete_nth_node(int n)
	{
		if (n < 1 || n > length)
			cout << "Error. No such nth node\n";
		else if (n == 1)
			delete_first();
		else {
			Node* before = get_nth(n - 1);
			Node* nth = before->next;
			bool istail = nth == Tail;
			before->next = nth->next;
			if (istail)
				Tail = before;
			delete_node(nth);
			debug_verify_data_integrity();
		}
	}
	////////////////////////////////////////////////////////////
	void delete_next_node(Node* node)
	{
		Node* to_delete = node->next;
		bool is_tail = to_delete == Tail;
		node->next = node->next->next;
		delete_node(to_delete);
		if (is_tail)
			Tail = node;
		debug_verify_data_integrity();

	}
	void delete_node_with_key(int value)
	{
		if (!length)
			cout << "Empty List " << endl;
		else if (Head->data == value)
			delete_first();
		else
		{
			for (Node* curr = Head, *prev = nullptr; curr; prev = curr, curr = curr->next)
			{
				if (curr->data == value)
				{
					delete_next_node(prev);
					break;
				}
			}
		}
		cout << "value not found" << endl;

	}

	
	void swap_head_tail()
	{
		if (length <= 1)
			return;
		Node* temp_head = Head;
		Head = Tail;
		Head->next = temp_head->next;
		Node* node_before_last = get_nth(length - 1);
		node_before_last->next = temp_head;
		Tail = temp_head;
		Tail->next = nullptr;
		debug_verify_data_integrity();
	}
	void left_rotate(int k)
	{
		if (length <= 1 || k % length == 0)
			return;
		k = k % length;
		Node* node = get_nth(k);
		Tail->next = Head;
		Head = node->next;
		Tail = node;
		Tail->next = nullptr;
		debug_verify_data_integrity();
	}
	void remove_duplicate() 
	{
		if (length <= 1)
			return;
		for(Node* curr1=Head;curr1;curr1=curr1->next) 
		{
			for (Node* curr2 = curr1->next , *prev=curr1;curr2 ;)
			{
				if (curr1->data == curr2->data)
				{
					delete_next_node(prev);
					curr2 = prev->next;
				}
				else
					prev = curr2, curr2 = curr2->next;
			}
		}
		debug_verify_data_integrity();
	}

};

void test1() {
	cout << "\n\ntest1\n";
	Linked_List list;
	list.insert_end(1);
	list.insert_end(2);

	list.insert_end(3);
	
	list.insert_end(4);
	
	list.insert_end(5);
	
	list.print();
	list.remove_duplicate();
	list.print();
	list.debug_print_address();
	list.debug_verify_data_integrity();
	string expected = "1 2 3 4 5";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}


int main()
{
	test1();
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";
	return 0;
}