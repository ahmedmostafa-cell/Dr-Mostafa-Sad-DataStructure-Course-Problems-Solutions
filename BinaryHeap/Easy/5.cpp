// ConsoleApplication21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <cassert>
using namespace std;
class MinHeap
{
    int size{};
    int capacity{ 1000 };
    int* array{};
    int left(int node) 
    {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        if (p >= size)
            return -1;
        return p;
    }
    int parent(int node)
    {
       
        return node==0?-1:(node-1)/2;
    }
    void heapify_up(int child_pos) 
    {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || array[par_pos] < array[child_pos])
            return;
        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }
    void heapify_down(int par_pos) 
    {
        int child_pos = left(par_pos);
        int right_pos = right(par_pos);
        if (child_pos == -1)
            return;
        if (right_pos != -1 && array[right_pos] < array[child_pos])
            child_pos = right_pos;
        if(array[child_pos]<array[par_pos]) 
        {
            swap(array[child_pos], array[par_pos]);
            heapify_down(child_pos);
        }
    }
    void heapify() 
    {
        for (int i = size / 2 - 1;i >= 0;i--)
            heapify_down(i);
    }
    public:
        MinHeap() 
        {
            array = new int[capacity];
            size = 0;
        }
        ~MinHeap() 
        {
            delete[] array;
            array = nullptr;
        }
        void push(int val) 
        {
            assert(size + 1 <= capacity);
            array[size++] = val;
            heapify_up(size - 1);
        }
        void pop() 
        {
            assert(!isempty());
            array[0] = array[--size];
            heapify_down(0);
        }
        bool isempty() 
        {
            return size == 0;
        }
        int top() 
        {
            return array[0];
        }
        void heap_sort(int *p,int n) 
        {
            int* oldarray = array;
            int oldsize = size;
            array = p;
            size = n;
            heapify();
            while(size--) 
            {
                swap(array[0], array[size]);
                heapify_down(0);
            }
            for(int i=0 ; i<n/2;i++) 
            {
                swap(array[i], array[n - i - 1]);
            }
            array = oldarray;
            size = oldsize;
        }

};
void heap_sort() {
    const int SZ = 14;
    int arr[SZ]{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MinHeap heap;

    heap.heap_sort(arr, SZ);

    for (int i = 0; i < SZ; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}
int main()
{
    heap_sort();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
