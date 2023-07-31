// VectorProblemNo1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
using namespace std;
class Vector 
{
    private :
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
        void set(int idx , int val) 
        {
            assert(0 <= idx && idx < size);
            arr[idx] = val;

        }
        void print() 
        {
            for(int i=0; i < size; i++) 
            {
                cout << arr[i] << " ";
               
            }
            cout << "\n";
        }
        void right_rotate() 
        {
            int lastElement = arr[size - 1];
            for(int i = size-1; i>0; i--) 
            {
                arr[i ] = arr[i-1];
            }
           
            arr[0] = lastElement;
           
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
    v.right_rotate();
    v.print();
}

