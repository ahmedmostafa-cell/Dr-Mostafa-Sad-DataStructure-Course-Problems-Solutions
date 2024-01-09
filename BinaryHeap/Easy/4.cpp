// ConsoleApplication18.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    int parnet(int node)
    {
        return node == 0 ? -1 : (node - 1) / 2;
    }
    void heapify_up(int child_pos)
    {
        int par_cpos = parnet(child_pos);
        if (child_pos == 0 || array[par_cpos] < array[child_pos])
            return;
        swap(array[par_cpos], array[child_pos]);
        heapify_up(par_cpos);
    }
    void heapify_down(int par_pos)
    {
        int child_pos = left(par_pos);
        int right_pos = right(par_pos);
        if (child_pos == -1)
            return;
        if (right_pos != -1 && array[right_pos] < array[child_pos])
            child_pos = right_pos;
        if (array[par_pos] > array[child_pos])
        {
            swap(array[par_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }
    void heapify()
    {
        for (int i = size / 2 - 1;i >= 0;i--)
        {
            heapify_down(i);
        }
    }
public:
    MinHeap()
    {
        array = new int[capacity];
        size = 0;
    }
    MinHeap(vector<int> v)
    {
        array = new int[capacity];
        size = (int)v.size();
        for (int i = 0;i < (int)v.size();i++)
        {
            array[i] = v[i];
        }
        heapify();
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
    void print_less(int val, int par_pos = 0)
    {
        if (par_pos >= size)
            return;
        if (array[par_pos] < val)
            cout << array[par_pos] << " ";
        int l = left(par_pos);
        if (array[l] < val)
            return print_less(val, l);
        int r = right(par_pos);
        if (array[r] < val)
            return print_less(val, r);
    }
    bool isheap(int par_pos) 
    {
        if (par_pos<0)
            return true;
        int l = left(par_pos);
        if (l != -1 && array[par_pos] > array[l])
            return false;
        
        int r = right(par_pos);
        if (r!=-1&& array[par_pos] > array[r])
            return false;
       
        return isheap(l) && isheap(r);
    }
    bool is_heap_array(int * p , int n) 
    {
        int* old_arr = array;
        int old_size = size;

        array = p;
        size = n;

        bool result = isheap(0);

        size = old_size;
        array = old_arr;

        return result;
    }
};
class MaxHeap
{
private:
    MinHeap h;
    vector<int> multi(const vector<int>& v)
    {
        vector<int> res;

        for (int i = 0;i < (int)v.size();i++)
        {
            res.push_back(-1 * v[i]);
        }
        return res;
    }
public:
    MaxHeap() {};
    MaxHeap(vector<int> v) : h(multi(v)) {}
    void push(int val)
    {
        h.push(val);
    }
    void pop()
    {
        h.pop();
    }
    bool isempty()
    {
        return h.isempty();
    }
    int top()
    {
        return h.top();
    }
};
void creat_heap_n() {
   
    MinHeap heap;
  
    int arr[]{ 2, 5, 12, 7,6, 22, 14, 19, 10, 17, 8, 37, 25, 30 };
    cout << heap.is_heap_array(arr, 14) << "\n";	// 1
    swap(arr[0], arr[5]);
    cout << heap.is_heap_array(arr, 14) << "\n";	// 0
   
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
