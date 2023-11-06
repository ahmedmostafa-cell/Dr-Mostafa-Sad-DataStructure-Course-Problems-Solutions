#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int aded_elements{ };
	int* array{ };
public:
	Stack(int size) :
		size(size) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	bool push(int x) {
		if (isFull())
			return false;

		for(int i=aded_elements;i>0;i--) 
		{
			array[i] = array[i - 1];
		}
		array[0] = x;
		aded_elements++;
		return true;

	
		
	}

	bool pop() {
		if (isEmpty())
			return false;
		for (int i = 0;i <aded_elements-1;i++)
		{
			array[i] = array[i + 1];
		}

		aded_elements--;
		return true;
		
	}

	bool peek() {
		if (isEmpty())
			return false;
		return true;
	}

	int isFull() {
		return aded_elements == size;
	}

	int isEmpty() {
		return aded_elements == 0;
	}

	void display() {
		for (int i = 0; i < aded_elements; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};

int main() {


	Stack stk(3);
	stk.push(10);
	stk.display();
	stk.push(20);
	stk.display();
	stk.push(30);
	stk.display();
	stk.pop();
	stk.pop();
	stk.pop();
	stk.pop();
	stk.display();
	if (!stk.isFull())
		stk.push(50);
	else
		cout << "Full Stack\n";
	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30

	while (!stk.isEmpty()) {
		cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10

	return 0;
}
