#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

int count_unique_substrings(const string& str) {
	// O(L^3)
	// Try all possible substrings (L^2) and insert in hashset
	// Hashing a string is typically O(L)

	unordered_set<string> s;
	// List all substrings and add to the set
	for (int start = 0; start < (int)str.size(); ++start) {
		for (int end = start; end < (int)str.size(); ++end) {
			//cout<<str.substr(start, end - start + 1)<<", ";
			s.insert(str.substr(start, end - start + 1));
		}
	}

	return s.size();	// unique elements
	// Note: Using a trie: we can efficiently solve it in O(L^2)
	// Don't create the string and add to trie
	// For every stating position: let the second loop keep inserting
	// In trie letter by letter and mark as leaf
	// Hence overall only 2 loops
}
int count_substrings_match(const string& str1, const string& str2) {
	// Add all substrings
	unordered_set<string> s1;
	for (int start = 0; start < (int)str1.size(); ++start) {
		for (int end = start; end < (int)str1.size(); ++end) {
			s1.insert(str1.substr(start, end - start + 1));
		}
	}

	unordered_set<string> s2;
	for (int start = 0; start < (int)str2.size(); ++start) {
		for (int end = start; end < (int)str2.size(); ++end) {
			s2.insert(str2.substr(start, end - start + 1));
		}
	}
	int cnt = 0;
	for (string str : s1)
		cnt += s2.count(str);

	return cnt;
}

int main() {
	cout << count_unique_substrings("aaab") << "\n";	// 7
	cout << count_unique_substrings("aaaaa") << "\n";	// 5
	cout << count_unique_substrings("aaaba") << "\n";	// 11
	cout << count_unique_substrings("abcdef") << "\n";	// 21

	return 0;
}
