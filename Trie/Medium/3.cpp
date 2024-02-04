#include<iostream>
#include<vector>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf{ };

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}
	

	bool word_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return isLeaf;	// there is a string marked here

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return true;	// all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
	}
};


class Trie 
{
	private:
		static const int MAX_CHAR = 26;
		Trie* child[MAX_CHAR]{};
		bool isleaf{};
	public:
		Trie() 
		{
			memset(child, 0, sizeof(child));
		}
		void insert(string str, int idx = 0) 
		{
			if (idx == (int)str.size())
				isleaf = 1;
			else 
			{
				int cur = str[idx] - 'a';
				if (child[cur] == 0)
					child[cur] = new Trie();
				child[cur]->insert(str, idx + 1);
			}
		}
		void insert2(string str, int idx = 0) {
			Trie* cur = this;
			for (int i = 0;i < (int)str.size();i++)
			{
				int ch = str[i] - 'a';
				if (!cur->child[ch])
					cur->child[ch] = new Trie();
				cur = cur->child[ch];
			}
			
		}
		bool word_exist(string str, int idx = 0) 
		{
			if (idx == (int)str.size())
				return isleaf;
			int cur = str[idx] - 'a';
			if (!child[cur])
				return false;
			return child[cur]->word_exist(str, idx + 1);
		}
		bool word_exist2(string str, int idx = 0)
		{
			Trie* cur = this;
			for (int i = 0;i < (int)str.size();i++)
			{
				int ch = str[i] - 'a';
				if (!cur->child[ch])
					return false;
				cur = cur->child[ch];
			}
			return cur->isleaf;
			
		}
		bool prefix_exist(string str, int idx = 0) 
		{
			if (idx == (int)str.size())
				return true;
			int cur = str[idx] - 'a';
			if (!child[cur])
				return false;
			return child[cur]->prefix_exist(str, idx + 1);
		}
		void get_all_strings(vector<string>& res, string cur_str = "") 
		{
			if (isleaf)
				res.push_back(cur_str);
			for(int i=0;i <MAX_CHAR;i++) 
			{
				if (child[i])
					child[i]->get_all_strings(res, cur_str + (char)(i + 'a'));
			}

		}
		void auto_complete(const string& str, vector<string>& res) 
		{
			Trie* cur = this;
			for(int i=0; i <str.size();i++) 
			{
				int ch = str[i] - 'a';
				if (!cur->child[ch])
					return;
				cur = cur->child[ch];
			}
			cur->get_all_strings(res, str);
		}
		bool word_exist_with_1_change(string str) {
			// Brute force all possible 1-char change and search for it
			// O(L * 26 * L)
			for (int i = 0; i < (int)str.size(); ++i) {
				char cpy = str[i];
				for (char ch = 'a'; ch <= 'z'; ch++) {
					if (ch == cpy)	// Must do a change
						continue;
					str[i] = ch;
					if (word_exist(str))
						return true;
				}
				str[i] = cpy;	// copy back
			}
			return false;
		}
};

int main() {
	trie root;

	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";

	return 0;
}
