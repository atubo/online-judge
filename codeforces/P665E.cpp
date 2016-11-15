// http://codeforces.com/problemset/problem/665/E
#include <bits/stdc++.h>
using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        scanf("%d", &A[i]);\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << (i == (int)A.size()-1 ? "" : " ");
    }
    cout << endl;
}

class BinaryTrie {
public:
    class Node {
    public:
        Node():children(2, NULL), count(0) {}
        vector<Node*> children;
        int count;
    };

    int N;
    Node* root;

    BinaryTrie(int N_): N(N_) {
        root = new Node();
    }

    void insert(int x) {
        Node* node = root;
        node->count++;
        for (int i = N-1; i >= 0; i--) {
            int d = (x >> i) & 1;
            if (node->children[d] == NULL) {
                node->children[d] = new Node();
            }
            node = node->children[d];
            node->count++;
        }
    }
};

class Solution {
private:
    int N, K;
    vector<int> A;
public:
    Solution() {
        cin >> N >> K;
        A.resize(N);
        READ_ARRAY(N, A);
    }

    int calc(int x, const BinaryTrie& trie) {
        BinaryTrie::Node* node = trie.root;
        int ret = 0;
        int i;
        for (i = 31; i >= 0; i--) {
            int targeti = (K >> i) & 1;
            int xi = (x >> i) & 1;
            if (targeti == 0) {
                if (xi == 0) {
                    if (node->children[1]) ret += node->children[1]->count;
                    if (node->children[0]) node = node->children[0];
                    else break;
                } else {
                    if (node->children[0]) ret += node->children[0]->count;
                    if (node->children[1]) node = node->children[1];
                    else break;
                }
            } else {
                if (xi == 0) {
                    if (node->children[1]) node = node->children[1];
                    else break;
                } else {
                    if (node->children[0]) node = node->children[0];
                    else break;
                }
            }
        }
        if (i == -1) ret += node->count;
        return ret;
    }

    void solve() {
        BinaryTrie trie(32);
        trie.insert(0);
        int64_t ret = 0;
        int xorsum = 0;
        for (int x: A) {
            xorsum ^= x;
            ret += calc(xorsum, trie);
            trie.insert(xorsum);
        }
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
