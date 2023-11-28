// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

class priorityQueue
{
    private:
        int added_elements;
        int size{};
        Queue q1;
        Queue q2;
        Queue q3;
    public:
        priorityQueue(int size) : size(size), q1(size), q2(size), q3(size) {};
        int isEmpty()
        {
            return added_elements == 0;
        }
        bool isFull()
        {
            return added_elements == size;
        }
        void enqueue(int task_id ,  int priority) 
        {
            assert(!isFull());
            ++added_elements;
            if (priority == 1)
                q1.enqueue_rear(task_id);
            else if (priority == 2)
                q2.enqueue_rear(task_id);
            else if (priority == 3)
                q3.enqueue_rear(task_id);
            else
                assert(false);
        }
        int dequeue() 
        {
            assert(!isEmpty());
            while (!q3.isEmpty())
            {
                return q3.dequeue_front();
            } 
            while (!q2.isEmpty())
            {
                return q2.dequeue_front();
            }
            while (!q1.isEmpty())
            {
                return q1.dequeue_front();
            }
            --added_elements;
        }
        void display() 
        {
                if(!q3.isEmpty())
                    q3.display();
                if (!q2.isEmpty())
                    q2.display();
           
                if (!q1.isEmpty())
                    q1.display();
           
        }
};
int main()
{
    priorityQueue tasks(8);

    tasks.enqueue(1131, 1);
    tasks.enqueue(3111, 3);
    tasks.enqueue(2211, 2);
    tasks.enqueue(3161, 3);

    tasks.display();
    cout << tasks.dequeue() << "\n";	// 3111
    cout << tasks.dequeue() << "\n";	// 3161
    tasks.enqueue(1535, 1);
    tasks.enqueue(2815, 2);
    tasks.enqueue(3845, 3);
    tasks.enqueue(3145, 3);

    tasks.display();
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
