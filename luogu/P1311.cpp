// https://www.luogu.org/problem/show?pid=1311
// 选择客栈

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int N, K, P;
int pos[MAXN];
bool affordable[MAXN];

int main() {
    scanf("%d%d%d", &N, &K, &P);
    vector<vector<int>> lodge(K);
    pos[N] = INT_MAX;

    for (int i = 0; i < N; i++) {
        int c, p;
        scanf("%d%d", &c, &p);
        lodge[c].push_back(i);
        affordable[i] = (p <= P);
    }

    for (int i = N-1; i >= 0; i--) {
        if (affordable[i]) pos[i] = i;
        else pos[i] = pos[i+1];
    }

    int64_t res = 0;
    for (int k = 0; k < K; k++) {
        for (int x: lodge[k]) {
            int y = pos[x];
            if (y == INT_MAX) break;
            res += lodge[k].end() -
                lower_bound(lodge[k].begin(), lodge[k].end(), y) - (y == x);
        }
    }

    printf("%lld\n", res);
    return 0;
}
