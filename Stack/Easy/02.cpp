#include <iostream>
#include <cassert>
#include <string>
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
string reverse_sub(string line)
{
	line += ' ';
	string result;
	Stack s(line.size());
	for (int i = 0;i < line.size();i++)
	{
		if (line[i] != ' ')
			s.push(line[i]);
		else 
		{
			while (!s.isEmpty())
			{
				result += s.pop();
			}
			result += " ";
		}
			
		
	


	}
	return result;
}

int main() {


	string line;
	getline(cin, line);

	cout << reverse_sub(line) << "\n";

	return 0;
}
