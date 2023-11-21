// ConsoleApplication35.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
using namespace std;
typedef char type;
struct Node 
{
    type data{};
    Node* next{};
    Node(type data) : data(data) {};

};
class stack
{
    private :
        Node* head{};
    public:
        ~stack() 
        {
            while (!isEmpty())
            {
                pop();
            }
        }
        void push(type x) 
        {
            Node* node = new Node(x);
            node->next = head;
            head = node;

        }
        void display() 
        {
            for(Node* curr=head;curr;curr=curr->next) 
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
        int isEmpty() 
        {
            return !head;
        }
        type pop() 
        {
            assert(!isEmpty());
            type element = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
            return element;

        }
        type peek() 
        {
            return head->data;
        }
};
int precedence(char op) 
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

string InfixToPostfix(string postfix) 
{
    string to_postfix = "";
    for(int i=0;i<26;i++) 
    {
        to_postfix += (char)(i + 'a');
        to_postfix += (char)(i + 'A');
        if (i < 10)
            to_postfix += i;

    }
    string result;
    postfix += '-';
    stack operators;
    operators.push('#');
    for(int i =0; i<(int)postfix.size();i++) 
    {
        if (isdigit(postfix[i]))
            result += postfix[i];
        else if (to_postfix.find(postfix[i]) != string::npos)
            result += postfix[i];
        else if (postfix[i] == '(')
            operators.push(postfix[i]);
        else if (postfix[i]==')') 
        {
            while(operators.peek()!='(')
                result += operators.pop();
            operators.pop();
        }
        else 
        {
            while ( precedence(operators.peek()) > precedence(postfix[i]) ||
                precedence(postfix[i]) == precedence(operators.peek()) && postfix[i] != '^') 
            {
                result += operators.pop();
            }
            operators.push(postfix[i]);
                
           
            
        }
    }
    return result;
}
int main()
{
    std::cout << InfixToPostfix("4^3^2");
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
