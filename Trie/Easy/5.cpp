// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Trie 
{
    private:
        map<string, Trie*> child;
        bool isleaf{};
    public:
        void insert(const vector<string> &path) 
        {
            Trie* curr = this;
            for(int i=0; i<(int)path.size();i++) 
            {
                string ch = path[i];
                if (curr->child[ch] == 0)
                    curr->child[ch] = new Trie();
                curr = curr->child[ch];
            }
            isleaf = true;
        }
        bool subpath_exist(const vector<string>& path) 
        {
            Trie* curr = this;
            for (int i = 0; i < (int)path.size();i++)
            {
                string ch = path[i];
                if (!curr->child.count(ch))
                    return false;
                curr = curr->child[ch];
            }
            return true;
        }
};
int main()
{
    Trie root;
    vector<string> path {"home", "software", "eclipse", "bin"};
    root.insert(path);
    vector<string> path2 {"home", "software", "eclips"};
    std::cout << root.subpath_exist(path2);
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
