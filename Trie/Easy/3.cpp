// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
class Trie
{
    private:
        static const int MAX_CHAR = 26;
        Trie* child[MAX_CHAR];
        bool isleaf{};
    public:
        Trie() 
        {
            memset(child, 0, sizeof(child));
        }
        void insert(string str) 
        {
            reverse(str.begin(), str.end());
            Trie* curr = this;
            for(int i=0;i<(int)str.size();i++) 
            {
                int ch = str[i] - 'a';
                if (curr->child[ch] == 0)
                    curr->child[ch] = new Trie();
                curr = curr->child[ch];

            }
            curr->isleaf = 1;
                
           
        }
        bool suffix_exist(string str)
        {
            reverse(str.begin(), str.end());
            Trie* curr = this;
            for (int i = 0;i < (int)str.size();i++)
            {
                int ch = str[i] - 'a';
                if (curr->child[ch] == 0)
                    return false;
                curr = curr->child[ch];

            }
            return true;
        }
       
        bool prefix_exist(string str, int idx = 0)
        {
            if (idx == (int)str.size())
                return true;
            int ch = str[idx] - 'a';
            if (!child[ch])
                return false;

            return child[ch]->prefix_exist(str, idx + 1);
        }
        void exist(const string& str , int start_pos=0) 
        {
            Trie* t = this;
            for(int idx=start_pos;idx<(int)str.size();idx++) 
            {
                int ch = str[idx] - 'a';
                if (!t->child[ch])
                    return;
                t = t->child[ch];
                if (t->isleaf)
                    cout << str.substr(idx, idx + 1 - start_pos) << endl;
            }
           
         
        }
};
void list(const string &str , vector<string> q) 
{
    Trie t;
    for(int i=0;i<(int) q.size();i++) 
    {
        t.insert(q[i]);
    }
    for(int f=0;f<(int)str.size();f++) 
    {
        (t.exist(str, f));
      
          
    }
}
int main()
{
    Trie root;

    root.insert("abcd");
    root.insert("xyz");
    root.insert("abf");
    root.insert("xn");
    root.insert("ab");
    root.insert("bcd");

    cout << root.suffix_exist("cd") << "\n";
    cout << root.suffix_exist("cc") << "\n";
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
