// ConsoleApplication7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
using namespace std;
class Stack {
private:
	int size { };
	int top{ };
	int* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};

class Queue
{
private:
	int size{};
	int added_elements{ 0 };
	Stack s1;
	Stack s2;
public:
	Queue(int size) : size(size), s1(size), s2(size) {};
	int isEmpty()
	{
		return added_elements == 0;
	}
	bool isFull()
	{
		return added_elements == size;
	}
	void move(Stack& from, Stack& to)
	{
		while (!from.isEmpty())
		{
			to.push(from.pop());
		}
	}
	void enqueue(int value)
	{
		assert(!isFull());

		
		s1.push(value);
		
		++added_elements;
	}
	int dequeue()
	{
		assert(!isEmpty());
		while (!s1.isEmpty())
		{
			move(s1, s2);
		}
		int element = s2.peek();
		s2.pop();
		move(s2, s1);
		--added_elements;
		return element;
	}
};
int main()
{
	Queue qu(6);

	for (int i = 1; i <= 3; ++i)
		qu.enqueue(i);

	cout << qu.dequeue() << " ";
	cout << qu.dequeue() << " ";
	cout << qu.dequeue() << " ";
	

	while (!qu.isEmpty())
		cout << qu.dequeue() << " ";
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
