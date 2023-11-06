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
int revrse(int num)
{
	if (num == 0)
		return 0;
	int result;
	int num2 = 0;
	Stack s(100);
	while (num)
	{
		int a = num % 10;
		s.push(a);
		num = num / 10;
	}
	int tens = 1;
	while (!s.isEmpty())
	{
		num2 = (s.pop() * tens) + num2;
		tens *= 10;
	}
	return num2;
}

int main() {


	cout << revrse(12345) << endl;

	return 0;
}
