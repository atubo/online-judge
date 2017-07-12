// https://leetcode.com/problems/add-and-search-word-data-structure-design/#/description
// 211. Add and Search Word - Data structure design

#include <bits/stdc++.h>
using namespace std;

class WordDictionary {
    struct Node {
        Node(): children(26), isWord(false) {}
        vector<Node*> children;
        bool isWord;
    };
public:
    WordDictionary() {
        root = new Node;
    }

    void addWord(string word) {
        Node* curr = root;
        for (char c: word) {
            if (!curr->children[c-'a']) {
                curr->children[c-'a'] = new Node;
            }
            curr = curr->children[c-'a'];
        }
        curr->isWord = true;
    }

    bool search(string word) {
        return search(root, word, 0);
    }

    bool search(Node* curr, const string& word, int pos) {
        if (pos == (int)word.length()) return curr->isWord;
        char c = word[pos];
        if (c == '.') {
            for (int i = 0; i < 26; i++) {
                if (curr->children[i] && search(curr->children[i], word, pos+1)) {
                    return true;
                }
            }
            return false;
        } else {
            return curr->children[c-'a'] && search(curr->children[c-'a'], word, pos+1);
        }
    }

private:
    Node* root;
};

int main() {
    return 0;
}
