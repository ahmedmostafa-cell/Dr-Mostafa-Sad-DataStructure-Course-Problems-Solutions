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
	int find_transposition(int val)
	{


		for (int i = 0; i < size; ++i)
		{
			if (arr[i] == val)
			{

				if (i == 0)
					return 0;
				swap(arr[i], arr[i - 1]);




				return i - 1;
			}

		}

		return -1;
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


	cout << v.find_transposition(0);
	cout << "\n";
	v.print();
	return 0;
}

/*
* Problem #5: Improved search
Assume our vector is huge and we do many find() calls for almost a few small
repetitive values
One way to improve the code speed is: each time you find the value, you
shift it one step to the left
Eventually, the values that are queried a lot, will move to the head of array
Implement method: int find_transposition(int value)
It returns the found position, but consider moving it one step to the left
Example: 10 20 30 40 50. find_transposition(3)
New array 10 30 20 40 50
Return 1
*/