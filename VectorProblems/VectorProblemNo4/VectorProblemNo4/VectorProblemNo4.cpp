#include<iostream>
#include<cassert>
using namespace std;
class Vector
{
private:
	int* arr = nullptr;
	int size = 0;
	int capacity = 0;
public:
	Vector(int size) : size(size)
	{
		if (size == 0)
			size = 1;
		capacity = size + 10;
		arr = new int[capacity] {};
	}
	~Vector()
	{
		delete[]arr;
		arr = nullptr;
	}
	void right_rotate()
	{
		if (size <= 1)
			return;
		int lastNumber = arr[size - 1];
		for (int i = size - 1; i > 0; --i)
		{
			arr[i] = arr[i - 1];

		}
		arr[0] = lastNumber;

	}
	void right_rotate(int step_number)
	{

		int rotate_no = step_number % size;
		while (rotate_no--)
		{
			right_rotate();

		}

	}
	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			cout << arr[i] << " ";

		}
		cout << "\n";
	}
	void set(int idx, int val)
	{
		assert(0 <= idx && idx < size);

		arr[idx] = val;


	}
	int pop(int idx)
	{
		assert(0 <= idx && idx < size);
		int deleted_val = arr[idx];
		for (int i = idx; i < size; ++i)
		{
			arr[i] = arr[i + 1];

		}
		size--;
		return deleted_val;

	}
};
int main()
{
	int n = 6;
	Vector v(n);
	for (int i = 0; i < n; ++i)
	{
		v.set(i, i);

	}
	v.print();
	v.right_rotate(5);
	v.print();
	v.pop(3);
	v.print();


	return 0;
}


/*
* Problem #4: Deleting a position
Implement method int pop(int idx) in the vector class
It returns the deleted value
Remove this element from the array
Assume array is: 4 0 1 2 3
pop(2)
Return value 1
New array: 4 0 2 3
*/