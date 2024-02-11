// ConsoleApplication15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <queue>
using namespace std;
class AVL
{
private:
    struct BinaryNode
    {
        BinaryNode* left{};
        BinaryNode* right{};
      
        int height{};
        int data{};
        int ch_height(BinaryNode* node) 
        {
            if (!node)
                return -1;
            return node->height;
        }
        int update_height() 
        {
            return height = 1 + max(ch_height(left), ch_height(right));
        }
        int balance_factor() 
        {
            return ch_height(left) - ch_height(right);
        }
        BinaryNode(int data) : data(data) {};
      
    };
    BinaryNode* root{};
    BinaryNode* right_rotation(BinaryNode* Q)
    {
        cout << "right_rotation" << Q->data << endl;
        BinaryNode* p = Q->left;
        Q->left = p->right;
        p->right = Q;
        Q->update_height();
        p->update_height();
        return p;
    }
    BinaryNode* left_rotation(BinaryNode* P)
    {
        cout << "right_rotation" << P->data << endl;
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        Q->update_height();
        P->update_height();
        return Q;
    }
    BinaryNode* balance(BinaryNode* node)
    {
        if (node->balance_factor() == 2) 
        {
            if (node->left->balance_factor() == -1) 
            {
                node->left = left_rotation(node->left);
            }
            node = right_rotation(node);
        }
        else if (node->balance_factor() == -2) 
        {
            if (node->right->balance_factor() == 1) 
            {
                node->right = right_rotation(node->right);
            }
            node = left_rotation(node);
        }
           
               
       

        
         
               
      
        node->update_height();
        return node;
    }

    BinaryNode* insert(int target, BinaryNode* node)
    {
        if (target < node->data)
        {
            if (!node->left)
            {
                node->left = new BinaryNode(target);
            }
            else
            {
                node->left = insert(target, node->left);
            }


        }
        else if (target > node->data)
        {
            if (!node->right)
            {
                node->right = new BinaryNode(target);
            }
            else
            {
                node->right = insert(target, node->right);
            }


        }
        node->update_height();
        node = balance(node);
        return node;
    }
    BinaryNode* min_node(BinaryNode* curr)
    {
        while (curr && curr->left)
        {
            curr = curr->left;
        }
        return curr;
    }
    BinaryNode* delete_node(int target, BinaryNode* node)
    {
        if (!node)
            return nullptr;
        if (target < node->data)
        {
            node->left = delete_node(target, node->left);
        }
        else if (target > node->data)
        {
            node->right = delete_node(target, node->right);
        }
        else
        {
            BinaryNode* temp = node;
            if (!node->left && !node->right)
                node = nullptr;
            else if (!node->right)
                node = node->left;
            else if (!node->left)
                node = node->right;
            else
            {
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
            }

            if (temp)
                delete temp;

        }
        if (node)
        {
            node->update_height();
            node = balance(node);
        }
        return node;
    }
    bool is_bst(BinaryNode* node) 
    {
        bool lef = (!node->left || node->left->data < node->data && is_bst(node->left));
        if (!lef)
            return false;
        return (!node->right || node->right->data > node->data && is_bst(node->right));
    }
    void verify() 
    {
        assert(is_bst(root));
        assert( abs(root->balance_factor())<=1);
    }
    void print_inorder(BinaryNode* node) 
    {
        if (!node)
            return;
        print_inorder(node->left);
        cout << node->data << endl;
        print_inorder(node->right);

    }
    BinaryNode* lowBound(int target , BinaryNode* node) 
    {
        if (!node)
            return nullptr;
        BinaryNode* l{};
        if(target<=node->data) 
        {
           l = lowBound(target, node->left);
           if (l)
               return l;
           return node;
        }
       
        
        return  lowBound(target, node->right);
    }





    BinaryNode* upperBound(int target, BinaryNode* node) 
    {
        if (!node)
            return nullptr;
        if(target<node->data) 
        {
            BinaryNode* ans = upperBound(target, node->left);
            if (ans)
                return ans;
            return node;
        }
        return upperBound(target, node->right);

    }
    public:
        void insert_value(int target) 
        {
            if (!root) 
            {
                root = new BinaryNode(target);
            }
            else 
            {
                root = insert(target, root);
            }
              
          
            verify();
        }
        void delete_value(int target) 
        {
            if (root) 
            {
                root = delete_node(target, root);
                verify();
            }


        }
        void print_inorder() 
        {
            if (!root)
                return;
            print_inorder(root);
        }
        void level_order_traversal() 
        {
            if (!root)
                return;

            cout << "******************\n";
            queue<BinaryNode*> nodes_queue;
            nodes_queue.push(root);

            int level = 0;
            while (!nodes_queue.empty()) {
                int sz = nodes_queue.size();

                cout << "Level " << level << ": ";
                while (sz--) {
                    BinaryNode* cur = nodes_queue.front();
                    nodes_queue.pop();

                    cout << cur->data << " ";
                    if (cur->left)
                        nodes_queue.push(cur->left);
                    if (cur->right)
                        nodes_queue.push(cur->right);
                }
                level++;
                cout << "\n";
            }
        }
        pair<bool, int> lower_bound(int target)
        {
            if (!root)
                return make_pair(false, -1);
            BinaryNode* node = lowBound(target, root);
            if(node)
            {
                return make_pair(true, node->data);
            }
            return make_pair(false, -1);
        }







        pair<bool, int> upper_bound(int target) 
        {
            if (!root)
                return make_pair(false, -1);
            BinaryNode* node = upperBound(target, root);
            if(node) 
            {
                return make_pair(false, node->data);
            }
            else 
            {
                return make_pair(false, -1);
            }
        }

};
void f1() {
    AVL tree;

    for (int i = 0; i <= 32; ++i) {	// degenerate
        tree.insert_value(i);
        tree.level_order_traversal();
    }
}
void test_lower() {
    AVL tree;

    vector<int> v { 10, 5, 20, 15, 50, 70, 2, 13, 40 };
    // 2, 5, 10, 13, 15, 20, 40, 50, 70

    for (int i = 0; i < v.size(); ++i)
        tree.insert_value(v[i]);

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i)
        cout << v[i] + 1 << " " << tree.lower_bound(v[i] + 1).second << "\n";
}
void test_upper() {
    AVL tree;

    vector<int> v { 10, 5, 20, 15, 50, 70, 2, 13, 40 };

    for (int i = 0; i < v.size(); ++i)
        tree.insert_value(v[i]);

    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " " << tree.upper_bound(v[i]).second << "\n";
}
int main()
{
    test_upper();

    cout << "bye\n";

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
