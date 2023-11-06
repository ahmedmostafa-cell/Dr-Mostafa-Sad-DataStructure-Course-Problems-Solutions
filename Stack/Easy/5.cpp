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

string removeDuplicates(string str) {
	Stack s(str.size());

	for (int i = 0; i < (int)str.size(); ++i) {
		char ch = str[i];
		if (!s.isEmpty() && s.peek() == ch)
			s.pop();
		else
			s.push(ch);
	}
	str = "";
	while (!s.isEmpty())
		str = s.pop() + str;

	return str;
}


string removeDuplicates2(string str) 
{
	Stack sp(str.size());
	string result;
	for(int i =0; i<str.size();i++) 
	{
		if(sp.isEmpty()) 
		{
			sp.push(str[i]);
		}
		else 
		{
			if(sp.peek()==str[i]) 
			{
				sp.pop();
			}
			else 
			{
				sp.push(str[i]);
			}
		}
	}
	while (!sp.isEmpty())
	{
		result = sp.pop() + result;

	}
	return result;
}

int main() {
	cout << removeDuplicates2("abbacaac") << "\n";	// Empty
	cout << removeDuplicates2("aabacaacd") << "\n";	// bad
	cout << removeDuplicates2("abcddcba") << "\n";	// Empty

	return 0;
}
