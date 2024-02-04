// ConsoleApplication14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class Trie
{
    static const int MAX_CHAR = 26;
    Trie* child[MAX_CHAR];
    bool isleaf{};
    vector<int> indices;
    public:
        Trie() 
        {
            memset(child, 0, sizeof(child));
        }
        void insert(string str , int idx) 
        {
            Trie* curr = this;
            for(int i=0;i<(int)str.size();i++) 
            {
                int ch = str[i] - 'a';
                if(curr->child[ch]==0) 
                {
                    curr->child[ch] = new Trie();
                  
                  
                }
                curr->child[ch]->indices.push_back(idx);
                curr = curr->child[ch];
            }
            curr->isleaf = 1;
        }
        vector<int> get_prefixes(const string & str) 
        {
            Trie* curr = this;
            for(int i=0;i<(int)str.size();i++) 
            {
                int ch = str[i] - 'a';
                if (!curr->child[ch])
                    return vector<int>();
                curr = curr->child[ch];
            }
            return curr->indices;
        }
};
class WordFilter
{
    private:
        Trie root;
        Trie suffix_tree;
        vector<string> words_original;
    public:
        WordFilter(vector<string>& words) 
        {
            set<string> wordsset;
            words_original = words;
            for(int i=(int)words.size()-1;i>=0;i--) 
            {
                if(wordsset.insert(words[i]).second) 
                {
                    root.insert(words[i], i);
                    reverse(words[i].begin(), words[i].end());
                    suffix_tree.insert(words[i], i);
                }
            }

        }
        int f(string prefix , string suffix) 
        {
            vector<int> prefix_list = root.get_prefixes(prefix);
            reverse(suffix.begin(), suffix.end());
            vector<int> suffix_list = suffix_tree.get_prefixes(suffix);
            reverse(prefix_list.begin(), prefix_list.end());
            reverse(suffix_list.begin(), suffix_list.end());

            vector<int> common_data;	// It will contain all intersection between both
            set_intersection(prefix_list.begin(), prefix_list.end(), suffix_list.begin(), suffix_list.end(), back_inserter(common_data));

            if (common_data.size() == 0)
                return -1;
            return common_data.back();
        }
};
int main()
{
    vector<string> v {"abaa", "ab"};
    WordFilter filter(v);
    cout << filter.f("ab", "a") << "\n";
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
