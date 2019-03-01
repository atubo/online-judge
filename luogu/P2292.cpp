// https://www.luogu.org/problemnew/show/P2292
// [HNOI2004]L语言

#include <bits/stdc++.h>
using namespace std;

class Trie {
public:
    struct Node {
        Node *children[26];
        bool legal;
        Node() {
            memset(children, 0, 26*sizeof(Node*));
            legal = false;
        };
    };

    Trie() {
        root = new Node();
    }

    void add(const string &s) {
        Node* curr = root;
        for (char c : s) {
            if (!curr->children[c-'a']) {
                curr->children[c-'a'] = new Node();
            }
            curr = curr->children[c-'a'];
        }
        curr->legal = true;
    }

    Node* root;
};

const int MAXL = 1000010;
int N, M;
bool dp[MAXL];

int solve(const Trie &trie, const string &s) {
    int n = s.length();
    dp[0] = true;
    for (int i = 1; i <= n; i++) {
        Trie::Node* curr = trie.root;
        for (int l = 1; l <= min(i, 10); l++) {
            curr = curr->children[s[i-l]-'a'];
            if (!curr) break;
            if (dp[i-l] && curr->legal) {
                dp[i] = true;
                break;
            }
        }
    }
    int ans = 0;
    for (int i = n; i >= 0; i--) {
        if (dp[i]) {
            ans = i;
            break;
        }
    }
    memset(dp, 0, (n+1)*sizeof(bool));
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    Trie trie;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        trie.add(s);
    }
    for (int i = 0; i < M; i++) {
        string s;
        cin >> s;
        int ans = solve(trie, s);
        printf("%d\n", ans);
    }
    return 0;
}
