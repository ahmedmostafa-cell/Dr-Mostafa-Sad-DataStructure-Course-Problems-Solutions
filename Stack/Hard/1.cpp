#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top{ };
	double* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new double[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(double x) {
		assert(!isFull());
		array[++top] = x;
	}

	double pop() {
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

double ealuate (string postfix) 
{
	Stack sp(postfix.size());
	double result;
	for(int i=0;i<(int)postfix.size();i++) 
	{
		if (isdigit(postfix[i]))
			sp.push(postfix[i]-'0');
		else 
		{
			double a =  sp.pop();
			double b = sp.pop();
			if (postfix[i] == '*') 
			{
				result = (a * b);
				sp.push(result);
			}
			else if (postfix[i] == '+')
			{
				result = (a + b);
				sp.push(result);
			}
			else if (postfix[i] == '/')
			{
				result = (b/a);
				sp.push(result);
			}
			else if (postfix[i] == '-')
			{
				result = (b - a);
				sp.push(result);
			}
			else if (postfix[i] == '^')
			{
				result = pow(b,a);
				sp.push(result);
			}
			
				

		}
	}
	return sp.pop();
}

int main() {


	cout << ealuate("432^^");

	return 0;
}
