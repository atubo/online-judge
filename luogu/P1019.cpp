// https://www.luogu.org/problem/show?pid=1019
// 单词接龙

#include <bits/stdc++.h>
using namespace std;

int N;
int f[25][25];
int used[25];
int maxLen = 0;

void dfs(int u, int currLen) {
    used[u]++;
    maxLen = max(maxLen, currLen);

    for (int v = 0; v < N; v++) {
        if (f[u][v] > 0 && used[v] < 2) {
            dfs(v, currLen + f[u][v]);
        }
    }

    used[u]--;
}

void build(const vector<string>& words) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int L1 = words[i].length();
            int L2 = words[j].length();
            int k = 1;
            for (; k < min(L1, L2); k++) {
                if (words[i].substr(L1-k, k) == words[j].substr(0, k)) {
                    break;
                }
            }
            if (k != min(L1, L2)) {
                f[i][j] = L2 - k;
            }
        }
    }
}

int main() {
    cin >> N;
    vector<string> words(N);
    for (int i = 0; i < N; i++) {
        cin >> words[i];
    }

    build(words);

    char start;
    cin >> start;

    for (int i = 0; i < N; i++) {
        if (words[i][0] == start) {
            dfs(i, words[i].length());
        }
    }

    cout << maxLen << endl;
    return 0;
}
