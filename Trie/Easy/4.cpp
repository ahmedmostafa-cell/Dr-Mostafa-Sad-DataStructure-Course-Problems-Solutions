// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstring>
#include<map>
using namespace std;
class Trie
{
    private:
        map<int, Trie*> m;
        
        bool isleaf{};
    public:
       
        void insert(string str) 
        {
           
            Trie* curr = this;
            for(int i=0;i<(int)str.size();i++) 
            {
                int ch = str[i] - 'a';
                if (curr->m[ch] == 0)
                    curr->m[ch] = new Trie();
                curr = curr->m[ch];

            }
            curr->isleaf = 1;
                
           
        }
    
       
        bool word_exist(string str, int idx = 0)
        {
            if (idx == (int)str.size())
                return isleaf;
            int ch = str[idx] - 'a';
            if (!m[ch])
                return false;

            return m[ch]->word_exist(str, idx + 1);
        }
  
};

int main()
{
    Trie root;

    root.insert("abcd");
    root.insert("xyz");
    root.insert("abf");
    root.insert("xn");
    root.insert("ab");
    root.insert("bcd");

    cout << root.word_exist("xyz") << "\n";
    cout << root.word_exist("bcd") << "\n";
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
