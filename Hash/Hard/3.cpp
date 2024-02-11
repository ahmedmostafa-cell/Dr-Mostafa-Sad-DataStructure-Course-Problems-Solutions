// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;
int count_anagram_substring(const string &str) 
{
    unordered_set<string> s;
    for(int start =0;start<(int)str.size();start++) 
    {
        for(int end = start;end<(int)str.size();end++) 
        {
            string f = str.substr(start, end - start + 1);
            sort(f.begin(), f.end());
            s.insert(str.substr(start, end - start + 1));
        }
    }
    return s.size();
}

int main()
{
    std::cout << "Hello World!\n";
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
