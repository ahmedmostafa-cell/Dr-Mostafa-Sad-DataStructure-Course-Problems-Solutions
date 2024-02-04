// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class Trie
{
    private:
        static const int MAX_CHAR = 26;
        Trie* child[MAX_CHAR]{};
        bool isleaf{};
    public:
        void get_all_string(vector<string> &res , string curr_str="")
        {
            if (isleaf)
                res.push_back(curr_str);
            for(int i=0; i<MAX_CHAR;i++) 
            {
                if (child[i])
                    child[i]->get_all_string(res, curr_str + (char) (i + 'a'));
            }
        }
        void insert(string str) 
        {
            Trie* curr = this;
            for(int i=0;i<(int)str.size();i++) 
            {
                int ch = str[i] - 'a';
                if (curr->child[ch] == 0)
                    curr->child[ch] = new Trie();
                curr = curr->child[ch];
            }
            curr->isleaf= 1;
        }
};
int main()
{
    Trie root;
    root.insert("a");
    root.insert("ab");
    root.insert("abcd");
    root.insert("bcd");
    root.insert("xyz");
    root.insert("xyzw");
    vector<string> res;
    root.get_all_string(res);
    for (int i = 0;i < (int)res.size();i++)
        cout << res[i] << endl;
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
