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
	void right_rotatebyNewArray(int step_number)
	{

		int rotate_no = step_number % size;
		int* arr2 = new int[capacity] {};
		for (int i = 0; i < size; ++i)
		{
			if((i+ rotate_no)<size) 
			{
				arr2[i + rotate_no] = arr[i];
			}
			else 
			{
				arr2[(i + rotate_no)-size] = arr[i];
			}
			
				

		}
		swap(arr2, arr);
		delete[]arr2;
		

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
};
int main()
{
	int n = 5;
	Vector v(n);
	for (int i = 0; i < n; ++i)
	{
		v.set(i, i);

	}
	v.print();
	//v.right_rotate(9);
	v.right_rotatebyNewArray(10);
	v.print();


	return 0;
}


/*
Right rotation with steps
Implement void right_rotate(int times)
This one applies the right rotation times time
The challenge: times can be up to: 2000000000
Your code should be efficient to some extent
*/