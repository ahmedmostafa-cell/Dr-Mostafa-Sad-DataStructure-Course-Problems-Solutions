
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
	//Node* Tail{ nullptr };
	int length{ 0 };
	
public:
	void print()
	{
		for (Node* curr = Head; curr; curr = curr->Next)
		{
			cout << curr->data << " ";
		}
		cout << "\n";
	}
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
	void add_element(int data) 
	{
		Node* node = new Node(data);
		if(!Head) 
		{
			Head = node;
		}
		else 
		{
			node->Next = Head;
			Head = node;
		}
	}

	Node* get_tail() 
	{
		if (!Head)
			return nullptr;
		
		for (Node* curr = Head; curr; curr = curr->Next)
		{
			if (curr->Next == nullptr)
				return curr;


			
		}
		
	}


};
int main()
{
	Linked_List l;
	l.add_element(10);
	l.add_element(20);
	l.print();
	
	cout << l.get_tail()->data;
	return 0;
}