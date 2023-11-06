#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top{ };
	int end{ };
	int* array{ };
public:
	Stack(int size) :
		size(size), top(-1) , end(size) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int id, int x) {
		assert(!isFull());
		if(id==1) 
		{
			array[++top] = x;
		}
		else if(id==2) 
		{
			array[--end] = x;
		}
		
	}

	int pop(int id) {
		assert(!isEmpty(id));
		if (id == 1)
		{
			return array[top--];
		}
		else if (id == 2)
		{
			return array[end++];
		}
		
	}

	int peek(int id) {
		assert(!isEmpty(id));
		if (id == 1)
		{
			return array[top];
		}
		else if (id == 2)
		{
			return array[end];
		}
	}

	int isFull() {
		return top == size - 1 || end==0;
	}

	int isEmpty(int id) {
		if (id == 1)
		{
			return top == -1;
		}
		else if (id == 2)
		{
			return end == size;
		}
		
	}

	void display( int id) {
		if (id == 1)
		{
			for (int i = top; i >= 0; i--)
				cout << array[i] << " ";
			cout << "\n";
		}
		else if (id == 2)
		{
			for (int i = end; i < size; i++)
				cout << array[i] << " ";
			cout << "\n";
		}
		
	}
};

int main() {


	Stack stk(3);
	stk.push(2,10);
	stk.push(2,20);
	stk.push(2,30);



	if (!stk.isFull())
		stk.push(2,50);
	else
		cout << "Full Stack\n";
	stk.display(2);	// 30 20 10
	cout << stk.peek(2) << "\n";	// 30

	while (!stk.isEmpty(2)) {
		cout << stk.peek(2) << " ";
		stk.pop(2);
	} // 30 20 10

	return 0;
}
