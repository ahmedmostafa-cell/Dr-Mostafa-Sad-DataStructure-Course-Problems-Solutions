
#include<iostream>
#include<cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;
struct Node
{
    int data{ 0 };
    Node* Next{ nullptr };
    Node(int data) : data(data) {};
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};
class Linked_List
{
private:
    Node* Head{ nullptr };
    Node* Tail{ nullptr };
    int length{ 0 };
    vector<Node*>debud_data;
    void debug_add_node(Node* node)
    {
        debud_data.push_back(node);
    }
    void debug_remove_node(Node* node)
    {
        auto it = std::find(debud_data.begin(), debud_data.end(), node);
        if (it == debud_data.end())
            cout << "no nodes ";
        debud_data.erase(it);
    }
public:
    void print()
    {
        for (Node* curr = Head;curr;curr = curr->Next)
        {
            cout << curr->data << " ";
        }
        cout << "\n";
    }
    void print_recursive(Node* node)
    {
        if (node)
        {
            cout << node->data << " ";
            print_recursive(node->Next);

        }

    }
    void print_recursive_reverse(Node* node)
    {
        if (node)
        {
            print_recursive(node->Next);
            cout << node->data << " ";


        }

    }
    void insert_end(int data)
    {
        Node* node = new Node(data);
        add_node(node);
        if (!Head)
        {
            Head = Tail = node;
        }
        else
        {
            Tail->Next = node;
            Tail = node;

        }
        debug_verify_data_integrity();
    }
    void print_by_paraneter(Node* node)
    {
        while (node)
        {
            cout << node->data << " ";
            node = node->Next;

        }
        cout << "\n";

    }
    Node* get_head()
    {
        return Head;
    }
    Node* get_nth(int n)
    {
        int idx = 1;
        for (Node* curr = Head;curr;curr = curr->Next, idx++)
        {
            if (idx == n)
                return curr;
        }
        return nullptr;
    }
    int search(int data)
    {
        int idx = 0;
        for (Node* curr = Head;curr;curr = curr->Next, idx++)
        {
            if (curr->data == data)
                return idx;
        }
        return -1;

    }
    int improved_search(int data)
    {
        int idx = 0;
        for (Node* curr = Head, *prev = nullptr; curr; prev = curr, curr = curr->Next, idx++)
        {
            if (curr->data == data)
            {
                if (!prev)
                    return 0;
                else
                {
                    swap(prev->data, curr->data);
                    return idx - 1;
                }
            }



        }
        return -1;

    }
    void delete_first()
    {
        if (Head)
        {
            Node* node = Head;
            Head = Head->Next;
            delete_node(node);
            if (!Head)
                Tail = nullptr;

        }
        debug_verify_data_integrity();
    }
    void delete_last()
    {
        assert(length);

        if (length == 1)
        {
            delete_first();

        }
        else
        {
            Node* temp = get_nth(length - 1);
            delete_node(Tail);
            Tail = temp;
            Tail->Next = nullptr;
        }
        debug_verify_data_integrity();

    }
    void delete_nth_node(int n)
    {
        assert(length);
        Node* node = get_nth(n);
        assert(node);
        if (node == Head)
        {
            delete_first();
        }
        else if (node == Tail)
        {
            delete_last();
        }
        else
        {
            Node* prev = get_nth(n - 1);
            prev->Next = node->Next;
            delete_node(node);
        }
        debug_verify_data_integrity();

    }
    void delete_node(Node* node)
    {
        debug_remove_node(node);
        length--;
        delete(node);
    }


    void add_node(Node* node) {
        debug_add_node(node);
        ++length;
    }

    Linked_List() {
    }
    ~Linked_List() {};
    Linked_List(const Linked_List&) = delete;
    Linked_List& operator=(const Linked_List& another) = delete;

    void debug_print_address() {
        for (Node* cur = Head; cur; cur = cur->Next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }

    void debug_print_node(Node* node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if (node->Next == nullptr)
            cout << "X ";
        else
            cout << node->Next->data << " ";

        if (node == Head)
            cout << "head\n";
        else if (node == Tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "") {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int)debud_data.size(); ++i)
            debug_print_node(debud_data[i]);
        cout << "************\n" << flush;
    }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node* cur = Head; cur; cur = cur->Next) {
            oss << cur->data;
            if (cur->Next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(Head == nullptr);
            assert(Tail == nullptr);
            return;
        }

        assert(Head != nullptr);
        assert(Tail != nullptr);
        assert(Tail->Next == nullptr);

        if (length == 1)
            assert(Head == Tail);
        else {
            assert(Head != Tail);

            if (length == 2)
                assert(Head->Next == Tail);
            else if (length == 3) {
                assert(Head->Next);
                assert(Head->Next->Next == Tail);
            }
        }
        int len = 0;
        Node* prev = nullptr;
        for (Node* cur = Head; cur; prev = cur, cur = cur->Next, len++)
            assert(len < 10000);	// Consider infinite cycle?

        assert(length == len);
        assert(length == (int)debud_data.size());
        assert(prev == Tail);	// last node is tail
    }

    void destructor()
    {
        assert(length);
        Node* temp = Head;
        while (Head)
        {
            temp = Head->Next;
            delete_node(Head);
            Head = temp;


        }
        Tail = nullptr;
        debug_verify_data_integrity();
    }

    void delete_front()
    {
        if (Head)
        {
            Node* temp_head = Head;
            Head = Head->Next;
            delete_node(temp_head);
            if (length == 0)
                Tail = nullptr;
        }
    }

    void insert_front(int data)
    {
        Node* node = new Node(data);
        add_node(node);

        node->Next = Head;
        Head = node;
        if (length == 1)
            Tail = Head;


        debug_verify_data_integrity();
    }

    void delete_next_node(Node* node)
    {
        Node* to_delete = node->Next;
        bool istail = to_delete == Tail;
        node->Next = node->Next->Next;
        delete_node(to_delete);
        if (istail)
            Tail = node;

    }

    void reverse()
    {
        if (length <= 1)
            return;
        Tail = Head;
        Node* prev = Head;
       Head = Head->Next;
       while (Head)
       {
           Node* next = Head->Next;
           Head->Next = prev;
           prev = Head;
           Head = next;
          

       }
        Head = prev;
        Tail->Next = nullptr;
        debug_verify_data_integrity();
    }








    ////////////////////////////////////////////////////////////
};
void test1() {
    cout << "\n\ntest1\n";
    Linked_List list;
    list.insert_end(6);
    list.insert_end(10);
    list.insert_end(8);
    list.insert_end(15);
   
    list.print();
    list.reverse();
    // some actions
    list.print();
    list.debug_print_address();
    list.debug_verify_data_integrity();
    string expected = "15 8 10 6";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result
            << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test2() {
    cout << "\n\ntest2\n";
    Linked_List list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    // some actions
    list.print();
    list.debug_print_address();
    list.debug_verify_data_integrity();
    string expected = "1 2 3 4";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result
            << "\n";
        assert(false);
    }
    list.debug_print_list("********");















};
int main()
{

    test1();
    //test2();


    cout << "\n\nNO RTE\n";


}

