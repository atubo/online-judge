// https://leetcode.com/problems/prefix-and-suffix-search/
// 745. Prefix and Suffix Search

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Trie {
    struct Node {
        int val;
        Node* ch[27];
        Node(int x): val(x) {
            memset(ch, 0, sizeof(ch));
        }
    };
public:
    Trie() {
        root_ = new Node(-1);
    }

    void add(const string &w, int id) {
        Node *curr = root_;
        curr->val = max(curr->val, id);
        for (char c: w) {
            if (!curr->ch[c-'a']) curr->ch[c-'a'] = new Node(id);
            curr = curr->ch[c-'a'];
            curr->val = max(curr->val, id);
        }
    }

    int check(const string &s) {
        Node *curr = root_;
        for (char c: s) {
            if (!curr->ch[c-'a']) return -1;
            curr = curr->ch[c-'a'];
        }
        return curr->val;
    }
private:
    Node* root_;
};

class WordFilter {
public:
    WordFilter(vector<string> words) {
        for (int i = 0; i < (int)words.size(); i++) {
            string w = words[i];
            toId_[w] = i;

            int l = w.length();
            for (int j = 0; j <= l; j++) {
               string s = w.substr(j) + '{' + w.substr(0, j);
               trie_.add(s, i);
            }
        }
    }

    int f(string prefix, string suffix) {
        string key = suffix + '{' + prefix;
        int ans = trie_.check(key);
        const int l1 = prefix.length();
        const int l2 = suffix.length();
        for (int i = 0; i < min(l1, l2); i++) {
            if (prefix.substr(l1-1-i) != suffix.substr(0, i+1)) continue;
            string w = prefix.substr(0, l1-1-i) + suffix;
            if (toId_.count(w) > 0) {
                ans = max(ans, toId_.at(w));
            }
        }
        return ans;
    }

private:
    Trie trie_;
    map<string, int> toId_;
};

int main() {
    int n;
    cin >> n;
    vector<string> words;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        words.push_back(w);
    }
    WordFilter wf(words);
    cout << wf.f("", "abaa") << endl;
    return 0;
}
