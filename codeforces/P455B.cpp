// http://codeforces.com/problemset/problem/455/B

#include <bits/stdc++.h>

using namespace std;

class TrieNode {
public:
    TrieNode():children(26, NULL), normal(-1), misere(-1) {}
    vector<TrieNode*> children;
    int normal, misere;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c: word) {
            if (node->children[c-'a'] == NULL) {
                node->children[c-'a'] = new TrieNode();
            }
            node = node->children[c-'a'];
        }
    }

    void calcGrundy(TrieNode* node) {
        int normal = -1, misere = -1;
        for (auto child: node->children) {
            if (child) {
                calcGrundy(child);
                normal = (normal == -1 ?
                          child->normal : normal && child->normal);
                misere = (misere == -1 ?
                          child->misere : misere && child->misere);
            }
        }
        if (normal == -1) {
            assert(misere == -1);
            node->normal = 0;
            node->misere = 1;
        } else {
            node->normal = !normal;
            node->misere = !misere;
        }
    }
        
    TrieNode* root;
};

int main() {
    int N, K;
    cin >> N >> K;
    Trie trie;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        trie.insert(s);
    }

    trie.calcGrundy(trie.root);

    //printf("%d %d\n", trie.root->normal, trie.root->misere);
    const int normal = trie.root->normal;
    const int misere = trie.root->misere;
    const string first = "First", second = "Second";
    if (normal == 1 && misere == 0) {
        cout << (K % 2 == 1 ? first : second) << endl;
    } else if (normal == 1 && misere == 1) {
        cout << first << endl;
    } else {
        cout << second << endl;
    }

    return 0;
}
