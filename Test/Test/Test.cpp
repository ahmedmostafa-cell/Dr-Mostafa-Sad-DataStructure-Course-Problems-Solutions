// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
using namespace std;
class Vector 
{
    private :
        int* arr{nullptr};
        int size{0};
        int capacity{0};
    public  :
        Vector(int size) : size(size) 
        {
            if (size < 0)
                size = 1;
            capacity = size + 10;
            arr = new int[capacity] {};
        }
        ~Vector()
        {
            delete[]arr;
            arr = nullptr;
        }
        void set(int idx , int val) 
        {
            assert(0 <= idx && idx < capacity);
            arr[idx] = val;
        }
        void print()
        {
            for (int i = 0; i < size;++i)
            {
                cout << arr[i] << " ";
            }
            cout << "\n";

        }
        int get(int idx) 
        {
            assert(0 <= idx && idx < size);
            return arr[idx];
        }
        int find(int val) 
        {
            for (int i = 0; i < size;++i)
            {
                if(arr[i] == val) 
                {
                    return i;
                }
               
            }
           
        }
        int get_font() 
        {
            return arr[0];
        }
        int get_back()
        {
            return arr[size-1];
        }
        void expand_capacity()
        {
            capacity *= 2;
            int* arr2 = new int [capacity] {};
            for (int i = 0; i < size;++i)
            {
                arr2[i] = arr[i];

            }
            swap(arr2, arr);
            delete[]arr2;
            arr2 = nullptr;

        }
        void push_back(int val)
        {
            if (size == capacity)
                expand_capacity();

            arr[size++] = val;
        }
};
int main()
{
    int n = 2;
    Vector v(n);
    for(int i =0; i < n;++i) 
    {
        v.set(i, i);
    }
    v.print();
    cout << v.get(1);
    cout << "\n";
    cout << v.find(2);
    cout << "\n";
    cout << v.get_font();
    cout << "\n";
    cout << v.get_back();
    cout << "\n";

    v.push_back(1000);
    cout << "\n";
    v.print();
    cout << "\n";

    return 0;
}

