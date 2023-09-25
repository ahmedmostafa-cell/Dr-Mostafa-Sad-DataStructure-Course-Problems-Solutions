#include <iostream>
#include <cassert>
using namespace std;
class Vector
{
private:
    int* arr {nullptr};
    int size{ 0 };
    int capacity{};
public:
    Vector(int size) : size(size)
    {
        if (size == 0)
            size = 1;
        capacity = size + 10;
        arr = new int[capacity];
    }
    ~Vector()
    {
        delete[]arr;
        arr = nullptr;
    }
    void set(int idx, int val)
    {
        assert(0 <= idx && idx < size);
        arr[idx] = val;

    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";

        }
        cout << "\n";
    }
    void right_rotate()
    {
        int lastElement = arr[size - 1];
        for (int i = size - 1; i > 0; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[0] = lastElement;

    }
    void left_rotate()
    {
        int fstElement = arr[0];
        for (int i = 0; i < size-1; i++)
        {
            arr[i] = arr[i + 1];
        }

        arr[size-1] = fstElement;

    }

};

int main()
{
    int n = 10;
    Vector v(n);
    for (int i = 0; i < n; i++)
    {
        v.set(i, i);
    }
    v.print();
    v.left_rotate();
    v.print();
}


/*
roblem #2: Left rotation
Consider our Vector class. Add the member function: void left_rotate()
The function rotates the whole array 1 step to the left
However, in this case, the leftmost element will be 'rotated' around to the back of the array!
Example
Assume the array content is: 0 1 2 3 4
After a left rotation, it will be: 1 2 3 4 0
Notice how the 0 has 'rotated' to the tail of the array after applying left_rotate()
Ensure you avoid expanding the array's capacity
*/

