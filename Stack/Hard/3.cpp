#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

class Stack {
private:
	// Tip: We can make this struct internally
	struct Node {
		int data { };
		Node* next { };
		Node* prev{ };
		Node(int data) :
				data(data) {
		}
	};

	Node *head { };	
	Node* tail{ };	
	Node* middle{ };		// Points to Top
	int length = 0;
public:
	~Stack() {
		while (!isEmpty())
			pop();
	}
	void display() {
		for (Node* cur = head; cur; cur = cur->next) 
		{
			if(cur==middle)
				cout << "[" << cur->data << "]" << " ";
			else
				cout << cur->data << " ";
		}
			
		cout << "\n";
	}

	void link(Node* first, Node* second) 
	{
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
	}

	void push(int value) {
		
		Node* item = new Node(value);
		length += 1;
		if (!head)
			head = tail = item;
		else 
		{
			link(item, head);
			head = item;
			
		}
		if (length <= 1)
			middle =head;
		else if (length % 2 == 1)
			middle = middle->prev;
		
		

		
	}
	void pop() {
		assert(!isEmpty());
		Node* temp = head;
		head = head->next;
		delete temp;
		length -= 1;
		if (head)
			head->prev = nullptr;
		else if (!length)
			tail->next = nullptr;


		if (length <= 1)
			middle = head;
		else if (length % 2 == 0)
			middle = middle->next;
		




	}

	

	int peek() {
		assert(!isEmpty());
		int element = head->data;
		return element;
	}

	int isEmpty() {
		return !head;
	}
};

int main() {

	Stack stk;
	for (int i = 0; i < 10; ++i) {
		stk.push(i);
		stk.display();
	}
	while (!stk.isEmpty()) {
		stk.pop();
		stk.display();
	}
	return 0;
}

