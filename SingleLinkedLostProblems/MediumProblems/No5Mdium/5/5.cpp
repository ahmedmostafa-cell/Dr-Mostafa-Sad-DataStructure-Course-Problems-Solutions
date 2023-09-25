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
		cout << node->data << endl;
		delete node;
		--length;

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

	bool is_same(const Linked_List& other)
	{
		if (length != other.length)
			return false;
		Node* other_h = other.Head;
		for (Node* curr = Head; curr; curr = curr->next)
		{
			if (curr->data != other_h->data)
				return false;

			other_h = other_h->next;

		}
		return true;


	}


	bool is_same2(const Linked_List& other)
	{
		Node* h1 = Head;
		Node* h2 = other.Head;
		while (h1 && h2)
		{
			if (h1->data != h2->data)
				return false;
			h1 = h1->next;
			h2 = h2->next;

		}

		return !h1 && !h2;



	}

	////////////////////////////////////////////////////////////

	void delete_node_with_key(int value)
	{
		Node* prev = { nullptr };
		Node* temp = { nullptr };
		for (Node* curr = Head; curr; curr = curr->next)
		{
			if (curr->data == value)
			{
				if (!prev)
				{

					Head = curr->next;
					delete_node(curr);
					//delete_first();
				}
				else if (curr == Tail)
				{
					prev->next = nullptr;
					delete_node(Tail);
					Tail = prev;
				}
				else
				{

					prev->next = curr->next;
					delete_node(curr);

				}
			}
			prev = curr->next;
			debug_verify_data_integrity();
		}
		cout << "no same value" << endl;
	}






	void remove_last_occurence(int key)
	{
		assert(length);
		int idx = 1;
		int count = 0;
		for (Node* curr = Head;curr;curr = curr->next, idx++)
		{
			if (curr->data == key)
			{
				count == idx;
			}
		}
		if (count > 0)
		{
			delete_nth_node(idx);
		}
		else
		{
			cout << "key is not available" << endl;
		}
	}

	Node* move_to_end(Node* prev , Node* curr) 
	{
		
		if (curr == Tail)
			return curr;
		Node* next = curr->next;
		if(!prev) 
		{
			Head = next;
		}
		else 
		{
			prev->next = next;
		}

	
		Tail->next = curr;
		curr->next = nullptr;
		Tail = curr;
		return next;

	}

	void move_back(int key)
	{
		if (length <= 1)
			return;
		int len = length;
		for(Node* curr=Head,*prev=nullptr;len--;) 
		{
			
			if (curr->data == key)
			{
				curr = move_to_end(prev, curr);
			}
			else
				prev = curr, curr = curr->next;
		}

	}




};


void test1() {
	cout << "\n\ntest1\n";
	Linked_List list;
	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(4);
	list.insert_end(1);
	list.insert_end(7);
	list.insert_end(1);
	list.insert_end(8);
	list.insert_end(1);
	list.insert_end(1);

	list.print();
	list.move_back(1);
	list.print();
	list.debug_print_address();
	list.debug_verify_data_integrity();
	string expected = "2 3 2 4 7 8 1 1 1 1 1 1";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test2() {
	cout << "\n\ntest2\n";
	Linked_List list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	// some actions
	list.print();
	list.debug_print_address();
	list.debug_verify_data_integrity();
	string expected = "1 2 3 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");















};
int main()
{
	test1();

	//must see it, otherwise RTE
	cout << "\n\nNO RTE\n";
	return 0;
}

