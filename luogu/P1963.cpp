// https://www.luogu.org/problemnew/show/P1963
// [NOI2009]变换序列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int N;
int D[MAXN], T[MAXN], U[MAXN];

void dfs(vector<unordered_set<int>> &cand, int u) {
    assert((int)cand[u].size() == 1);
    int x = *cand[u].begin();
    T[x] = u;
    cand[u].erase(x);
    int t = (x + N - D[x]) % N;
    if (t == u) t = (x + D[x]) % N;
    cand[t].erase(x);
    if (cand[t].size() == 1) dfs(cand, t);
}

void dfs2(vector<unordered_set<int>> &cand, int u, int x) {
    assert((int)cand[u].size() == 2);
    T[x] = u;
    cand[u].erase(x);
    int x2 = *cand[u].begin();
    cand[u].erase(x2);
    int t = (x2 + N - D[x2]) % N;
    if (t == u) t = (x2 + D[x2]) % N;
    if (!cand[t].empty()) dfs2(cand, t, x2);
}


int main() {
    memset(T, -1, sizeof(T));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &D[i]);
    }
    vector<unordered_set<int>> cand(N);
    for (int i = 0; i < N; i++) {
        int x = (i + D[i]) % N;
        cand[x].insert(i);
        x = (i + N - D[i]) % N;
        cand[x].insert(i);
    }

    for (int i = 0; i < N; i++) {
        if ((int)cand[i].size() == 1) dfs(cand, i);
    }

    for (int i = 0; i < N; i++) {
        if (T[i] >= 0) U[T[i]] = 1;
    }

    for (int i = 0; i < N; i++) {
        if ((int)cand[i].size() != 2 && U[i] == 0) {
            printf("No Answer\n");
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        if (T[i] == -1) {
            int x = min((i+D[i])%N, (i+N-D[i])%N);
            dfs2(cand, x, i);
        }
    }
    for (int i = 0; i < N-1; i++) {
        printf("%d ", T[i]);
    }
    printf("%d\n", T[N-1]);
    return 0;
}
