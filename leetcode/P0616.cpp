// https://leetcode.com/problems/add-bold-tag-in-string/#/description
// 616. Add Bold Tag in String

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Node {
        Node(): isWord(false) {}
        map<char, Node*> children;
        bool isWord;
    };
public:
    string addBoldTag(string s, vector<string>& dict) {
        Node* root = new Node();
        for (const string& word: dict) {
            addWord(root, word);
        }

        const int N = s.length();
        vector<bool> mark(N);
        for (int i = 0; i < N; i++) {
            lookup(s, i, root, mark);
        }

        string ret = bold(s, mark);
        return ret;
    }

    void addWord(Node* root, const string& word) {
        Node* curr = root;
        for (char c: word) {
            if (!curr->children[c]) {
                curr->children[c] = new Node();
            }
            curr = curr->children[c];
        }
        curr->isWord = true;
    }

    void lookup(const string& s, int pos, Node* root, vector<bool>& mark) {
        int start = pos, last = pos - 1;
        Node* curr = root;
        while (pos < (int)s.length()) {
            char c = s[pos];
            if (curr->children.count(c) == 0) break;
            curr = curr->children[c];
            if (curr->isWord) last = pos;
            pos++;
        }
        for (int i = start; i <= last; i++) {
            mark[i] = true;
        }
    }

    string bold(const string& s, const vector<bool>& mark) {
        bool inBold = false;
        string ret;
        const int N = s.length();
        for (int i = 0; i < N; i++) {
            if (!inBold && mark[i]) {
                ret += "<b>";
                inBold = true;
            } else if (inBold && !mark[i]) {
                ret += "</b>";
                inBold = false;
            }
            ret += s[i];
        }
        if (inBold) ret += "</b>";
        return ret;
    }
};

int main() {
    string s;
    cin >> s;
    string tmp;
    getline(cin, tmp);
    vector<string> dict = getStringVector();
    Solution solution;
    auto ret = solution.addBoldTag(s, dict);
    cout << ret << endl;
    return 0;
}
