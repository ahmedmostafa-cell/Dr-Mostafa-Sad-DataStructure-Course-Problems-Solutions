// ConsoleApplication17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
class MinHeap
{
    private:
        int* array{};
        int size{};
        int capacity{ 1000 };
        int left(int node) 
        {
            int p = 2 * node + 1;
            if (p >= size)
                return-1;
            return p;
        }
        int right(int node)
        {
            int p = 2 * node + 2;
            if (p >= size)
                return-1;
            return p;
        }
        int parent(int node)
        {
            
            return node==0?-1:(node-1)/2;

        }
        void heapify_up(int child_pos) 
        {
            int parent_pos = parent(child_pos);
            if (child_pos == 0 || array[parent_pos] < array[child_pos])
                return;
            swap(array[child_pos], array[parent_pos]);
            heapify_up(parent_pos);
        }
        void heapify_down(int par_pos) 
        {
            int lef = left(par_pos);
            int r = right(par_pos);
            if (lef == -1)
                return;
            if (r != -1 && array[r] < array[lef])
                lef = r;
            if(array[par_pos]>array[lef]) 
            {
                swap(array[par_pos], array[lef]);
                heapify_down(lef);
            }

        }
    public:
        MinHeap() 
        {
            array = new int[capacity];
            size = 0;

        }
        ~MinHeap() 
        {
            delete[]array;
            array = nullptr;
        }
        bool isempty() 
        {
            return size == 0;
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
        int top() 
        {
            return array[0];
        }
};


class MaxHeap
{
private:
    int* array{};
    int size{};
    int capacity{ 1000 };
    int left(int node)
    {
        int p = 2 * node + 1;
        if (p >= size)
            return-1;
        return p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        if (p >= size)
            return-1;
        return p;
    }
    int parent(int node)
    {

        return node == 0 ? -1 : (node - 1) / 2;

    }
    void heapify_up(int child_pos)
    {
        int parent_pos = parent(child_pos);
        if (child_pos == 0 || array[parent_pos] > array[child_pos])
            return;
        swap(array[child_pos], array[parent_pos]);
        heapify_up(parent_pos);
    }
    void heapify_down(int par_pos)
    {
        int lef = left(par_pos);
        int r = right(par_pos);
        if (lef == -1)
            return;
        if (r != -1 && array[r] > array[lef])
            lef = r;
        if (array[par_pos] < array[lef])
        {
            swap(array[par_pos], array[lef]);
            heapify_down(lef);
        }

    }
    void heapify() 
    {
        for(int i = size/2-1;i>=0;i--) 
        {
            heapify_down(i);
        }
    }
public:
    MaxHeap()
    {
        array = new int[capacity];
        size = 0;

    }
    MaxHeap(vector<int>v)
    {
        array = new int[capacity];
        size = v.size();
        for(int i =0;i<(int)v.size();i++) 
        {
            array[i] = v[i];
        }
        heapify();
    }
    ~MaxHeap()
    {
        delete[]array;
        array = nullptr;
    }
    bool isempty()
    {
        return size == 0;
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
    int top()
    {
        return array[0];
    }
};



void creat_heap_nlogn() {
    MinHeap heap;

    vector<int> v { 2, 17, 22, 10, 8, 37,
        14, 19, 7, 6, 5, 12, 25, 30 };

    for (int i = 0; i < v.size(); ++i)
        heap.push(v[i]);

    while (!heap.isempty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
    // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void creat_heap_n() {
    vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MaxHeap heap(v);

    //h.print();
    while (!heap.isempty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
}
int main()
{
    creat_heap_n();
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
