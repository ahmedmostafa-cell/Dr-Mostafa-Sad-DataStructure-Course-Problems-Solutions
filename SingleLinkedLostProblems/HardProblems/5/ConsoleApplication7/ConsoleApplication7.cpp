
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
			bool istail = nth = Tail;
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

	void arrange_odd_even()
	{
		if (length <= 2)
			return;
		Node* curr_odd = Head;
		Node* first_even = Head->next;
		while (curr_odd->next && curr_odd->next->next)
		{
			Node* next_even = curr_odd->next;
			curr_odd->next = curr_odd->next->next;
			next_even->next = next_even->next->next;
			if (length % 2 == 1)
				Tail = next_even;
			curr_odd = curr_odd->next;

		}
		curr_odd->next = first_even;
		debug_verify_data_integrity();
	}

	void alternate(Node* curr1, Node* curr2)
	{
		curr2->next = curr1->next;
		curr1->next = curr2;
		add_node(curr2);
	}

	void insert_alternate(Linked_List& another)
	{
		if (!another.length)
			return;
		if (!length)
		{
			Head = another.Head;
			Tail = another.Tail;
			length = another.length;
			debug_data = another.debug_data;

		}
		else
		{
			Node* curr1 = Head;
			Node* curr2 = another.Head;
			while (curr1 && curr2)
			{
				Node* curr2_next = curr2->next;
				alternate(curr1, curr2);
				--another.length;
				curr2 = curr2_next;

				if (curr1 == Tail)
				{
					length += another.length;
					curr1->next->next = curr2;
					Tail = another.Tail;
					break;
				}
				curr1 = curr1->next->next;

			}
		}
	}

	void insert_front(int value) {
		Node* item = new Node(value);
		add_node(item);

		item->next = Head;
		Head = item;

		if (length == 1)
			Tail = Head;
	}

	Node* move_delete(Node* curr)
	{
		Node* temp = curr->next;
		delete_node(curr);
		return temp;
	}

	void remove_repeated()
	{
		if (length <= 1)
			return;
		insert_front(-1234);
		Tail = Head;
		Node* prev = Head;
		Node* curr = Head->next;
		while (curr)
		{
			bool any_removed = false;
			while (curr && curr->next && curr->data == curr->next->data)
			{
				any_removed = true;
				int block = curr->data;
				while (curr && curr->data == block)
				{
					curr = move_delete(curr);
				}
			}
			if (any_removed)
			{
				if (!curr)
				{
					Tail = prev;

				}

				prev->next = curr;
				prev = curr;
				Tail = curr;
			}
			else
			{
				prev = curr;
				curr = curr->next;
				Tail = prev;
			}

		}
		prev = Head->next;

		delete_first();
		if (!Head)
		{
			Tail = Head;

		}

		debug_verify_data_integrity();
	}

	pair<Node* , pair<Node* , Node*>> reverse(Node* curr_head , int k) 
	{
		Node* curr_tail = curr_head;
		Node* prev = curr_head;
		curr_head = curr_head->next;
		for(int s=0;s<k-1&&curr_head;s++) 
		{
			Node* next = curr_head->next;
			curr_head->next = prev;
			prev = curr_head;
			curr_head = next;
		}
		return make_pair(prev, make_pair(curr_tail, curr_head));
	}

	void reverse_chains(int k) 
	{
		Node* next_chain_head = Head;
		Head = nullptr;
		Node* last_tail = nullptr;
		while (next_chain_head)
		{
			pair<Node*, pair<Node*, Node*>> p = reverse(next_chain_head, k);
			Node* chain_head = p.first;
			Node* chain_tail = p.second.first;
			next_chain_head = p.second.second;
			Tail = chain_tail;
			if (!Head)
				Head = chain_head;
			else
				last_tail->next = chain_head;
			
			last_tail = chain_tail;

		}
		Tail->next = nullptr;
	}
};


void test1() {
	cout << "\n\ntest1\n";
	Linked_List list;
	Linked_List list2;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	
	list.reverse_chains(6);
	// some actions
	list.print();
	list.debug_print_address();
	list.debug_verify_data_integrity();
	string expected = "6 5 4 3 2 1";
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

