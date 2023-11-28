// ConsoleApplication10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
using namespace std;
class Queue
{
private:
    int size{};
    int added_elements{};
    int front{ 0 };
    int rear{ 0 };
    int* array{ nullptr };
public:
    Queue(int size) : size(size)
    {
        array = new int[size];
    };
    ~Queue()
    {
        delete[]array;
    }
    int isEmpty()
    {
        return added_elements == 0;
    }
    bool isFull()
    {
        return added_elements == size;
    }
    int next(int pos)
    {
        ++pos;
        if (pos == size)
            return 0;
        return pos;
    }
    int prev(int pos)
    {
        --pos;
        if (pos == -1)
            return size - 1;
        return pos;
    }
    void enqueue_rear(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        ++added_elements;

    }
    void enqueue_front(int value)
    {
        assert(!isFull());
        front = prev(front);
        array[front] = value;
        ++added_elements;

    }
    int dequeue_front()
    {
        assert(!isEmpty());
        int element = array[front];
        front = next(front);
        --added_elements;
        return element;
    }
    int dequeue_rear()
    {
        assert(!isEmpty());

        rear = prev(rear);
        int element = array[rear];
        --added_elements;
        return element;
    }
    void display()
    {
        for (int curr = front, step = 0;step < added_elements;step++, curr = next(curr))
        {
            cout << array[curr] << " ";
        }
        cout << endl;
    }
};
class Last_k_numbers_sum_stream
{
private:
    int sum;
    Queue q;
public:
    Last_k_numbers_sum_stream(int k) : q(k + 1)
    {

    };
    int next(int new_num)
    {
        sum += new_num;
        q.enqueue_rear(new_num);
        if (q.isFull())
        {
            sum -= q.dequeue_front();

        }



        return sum;
    }
};
int main()
{
    Last_k_numbers_sum_stream processor(4);

    int num;
    while (cin >> num)
        cout << processor.next(num) << "\n";

    return 0;
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
