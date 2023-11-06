#include <iostream>
#include <cassert>
using namespace std;

// simple trick to avoid re-changing the class
typedef char type;

class Stack {
private:
	int size { };
	int top{ };
	type* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new type[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(type x) {
		assert(!isFull());
		array[++top] = x;
	}

	type pop() {
		assert(!isEmpty());
		return array[top--];
	}

	type peek() {
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

char get_open_match(char ch) {
	if (ch == ')')
		return '(';
	if (ch == ']')
		return '[';
	return '{';
}

bool isValid(string str) {
	Stack parentheses(str.size());

	for (int i = 0; i < (int)str.size(); ++i) {
		char ch = str[i];

		if (ch == '(' || ch == '[' || ch == '{')
			parentheses.push(ch);
		else if (parentheses.isEmpty() || parentheses.pop() != get_open_match(ch))
			return false;	// There must be an open match of the right type
	}
	return parentheses.isEmpty();
}

bool isValid2(string str) 
{
	Stack sp(str.size());
	for(int i =0;i<str.size();i++) 
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			sp.push(str[i]);
		else 
		{
			if (sp.isEmpty())
				return false;
			else 
			{
				if (str[i] == ')' && sp.peek() == '(')
				{
					sp.pop();
				}
				else if (str[i] == '}' && sp.peek() == '{')
				{
					sp.pop();
				}
				else if (str[i] == ']' && sp.peek() == '[')
				{
					sp.pop();
				}
				else
					return false;
			}
				
			
					
				

		}
		

	}
	if (!sp.isEmpty())
		return false;
	return true;
}

int main() {
	cout << isValid2("(())") << "\n";		// 1
	cout << isValid2("(()[()])") << "\n";	// 1
	cout << isValid2("(][)") << "\n";		// 0
	cout << isValid2("(()") << "\n";		// 0
	cout << isValid2("()(") << "\n";		// 0

	return 0;
}
