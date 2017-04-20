// https://www.luogu.org/problem/show?pid=1955
// 程序自动分析

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int N;
const int MAXN = 100010;
int X[MAXN], Y[MAXN], E[MAXN];
int fa[2*MAXN];
unordered_map<int, int> id;

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%d", &N);
        int cnt = 0;
        id.clear();
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d", &X[i], &Y[i], &E[i]);
            if (!id.count(X[i])) id[X[i]] = cnt++;
            if (!id.count(Y[i])) id[Y[i]] = cnt++;
            X[i] = id[X[i]];
            Y[i] = id[Y[i]];
        }
        for (int i = 0; i < cnt; i++) fa[i] = i;
        for (int i = 0; i < N; i++) {
            int u = find(X[i]), v = find(Y[i]);
            if (E[i]) fa[v] = u;
        }
        bool conflict = false;
        for (int i = 0; i < N; i++) {
            int u = find(X[i]), v = find(Y[i]);
            if (!E[i]) {
                if (u == v) {
                    conflict = true;
                    break;
                }
            }
        }
        printf(conflict ? "NO\n" : "YES\n");
    }
    return 0;
}
