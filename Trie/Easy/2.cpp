// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
class Trie
{
    private:
        static const int MAX_CHARR = 26;
        Trie* child[MAX_CHARR];
        bool isleaf{};
    public:
        Trie() 
        {
            memset(child, 0, sizeof(child));
        }
        void insert(string str , int idx=0)
        {
            if (idx == (int)str.size())
                isleaf = 1;
            else 
            {
                int curr = str[idx] - 'a';
                if (child[curr] == 0)
                    child[curr] = new Trie();
                child[curr]->insert(str, idx + 1);
            }
        }
        void insert2(string str)
        {
            Trie* cur = this;
            for (int i = 0;i < (int)str.size();i++)
            {
                int ch = str[i] - 'a';
                if (!cur->child[ch])
                    cur->child[ch] = new Trie();
                cur = cur->child[ch];
                if (i == (int)str.size() - 1)
                    cur->isleaf = 1;
               
            }
        }
        bool word_exist(string str, int idx = 0)
        {
            if (idx == (int)str.size())
                return isleaf;
            
                int curr = str[idx] - 'a';
                if (!child[curr])
                    return false;
                return child[curr]->word_exist(str, idx + 1);
        }
        bool word_exist2(string str)
        {
           


            Trie* cur = this;
            for (int i = 0;i < (int)str.size();i++)
            {
                int ch = str[i] - 'a';
                if (!cur->child[ch])
                    return false;
                cur = cur->child[ch];
                if (i == (int)str.size() - 1)
                    return cur->isleaf;

            }
        }
        bool prefix_exist(string str, int idx = 0)
        {
            if (idx == (int)str.size())
                return true;

            int curr = str[idx] - 'a';
            if (!child[curr])
                return false;
            return child[curr]->prefix_exist(str, idx + 1);
        }
        bool word_wonechange_exist(string str, int idx = 0)
        {
            for(int i=0;i<(int)str.size();i++) 
            {
                char c = str[i];
                for(char f = 'a';f<'z'; f++) 
                {
                    if (f == c)
                        continue;
                    str[i] = f;
                    if (word_exist(str))
                        return true;
                }
                str[i] = c;
            }
            return false;
        }
        bool q_exits(string str) 
        {
            Trie* t = this;
           
                if (prefix_exist(str))
                    return true;
            
            return false;
        }
        void print_all_matches(const string& str,int start_pos=0) 
        {
            Trie* cur = this;
            for(int idx=start_pos;idx<(int) str.size();idx++) 
            {
                int ch = str[idx]-'a';
                if (!cur->child[ch])
                    return;
                cur = cur->child[ch];
                if (cur->isleaf)
                    cout << str.substr(start_pos, idx - start_pos + 1) << endl;
            }
        }
        string first(const string& str)
        {
            Trie* cur = this;
            string w = "";
            for (int idx = 0; idx < (int)str.size(); ++idx) {
                int ch = str[idx] - 'a';
                if (!cur->child[ch])
                    return w;	// such path don't exist
                w += str[idx];
                cur = cur->child[ch];
                if (cur->isleaf)
                    return w;
            }
            return w;
        }
};

void list(const string& str, vector<string> q) 
{
    Trie t;
    for(int i=0;i<(int)str.size();i++) 
    {
        t.insert(str, i);
    }
    for(int f=0;f<(int)q.size();f++) 
    {
        if (t.q_exits(q[f]))
            cout << q[f] << endl;
    }
}
void list2(const string& str, vector<string> q)
{
    Trie t;
    for (int i = 0;i < q.size();i++)
    {
        t.insert(q[i]);
    }
    for (int i = 0;i < (int)str.size();i++)
    {
        t.print_all_matches(str, i);
    }
}
int main()
{
    Trie root;

    root.insert("xyz");
    root.insert("xyzwfe");



    cout << root.first("xyeee") << "\n";
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
