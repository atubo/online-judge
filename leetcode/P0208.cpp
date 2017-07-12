// https://leetcode.com/problems/implement-trie-prefix-tree/#/description
// 208. Implement Trie (Prefix Tree)

#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        Node(): children(26), isWord(false) {}
        vector<Node*> children;
        bool isWord;
    };

public:
    Trie() {
        root = new Node;
    }

    void insert(string word) {
        Node* curr = root;
        for (char c: word) {
            Node* next = curr->children[c-'a'];
            if (!next) {
                next = curr->children[c-'a'] = new Node;
            }
            curr = next;
        }
        curr->isWord = true;
    }

    bool search(string word) {
        Node* curr = root;
        for (char c: word) {
            Node* next = curr->children[c-'a'];
            if (!next) return false;
            curr = next;
        }
        return curr->isWord;
    }

    bool startsWith(string prefix) {
        Node* curr = root;
        for (char c: prefix) {
            Node* next = curr->children[c-'a'];
            if (!next) return false;
            curr = next;
        }
        return true;
    }

private:
    Node* root;
};

int main() {
    return 0;
}
