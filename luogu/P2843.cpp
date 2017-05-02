// https://www.luogu.org/problem/show?pid=2843
// 暗杀

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int ps[MAXN][31];

int main() {
    scanf("%d%d", &N, &K);
    if (K == 1) {
        printf("%d\n", N);
        return 0;
    }
    int ret = 0;
    map<vector<int>, int> m;
    vector<int> key(K-1);
    m[key] = 0;
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        for (int k = 0; k < K; k++) {
            ps[i][k] = ps[i-1][k];
            if ((a >> k) & 1) ps[i][k]++;
        }
        for (int k = 1; k < K; k++) {
            key[k-1] = (ps[i][k] - ps[i][0]);
        }
        auto it = m.find(key);
        if (it == m.end()) {
            m[key] = i;
        } else {
            ret = max(ret, i - m[key]);
        }
    }
    printf("%d\n", ret);
    return 0;
}
