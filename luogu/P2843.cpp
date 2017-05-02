// https://www.luogu.org/problem/show?pid=2843
// 暗杀

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int ps[MAXN][31];

const int PRIME1 = 22279;
const int PRIME2 = 982451653;

namespace std {
template<>
struct hash<vector<int>> {
    size_t operator()(const vector<int> &v) const {
        size_t ret = 0;
        for (int x: v) {
            ret = (ret * PRIME1 + x) % PRIME2;
        }
        return ret;
    }
};
}

int main() {
    scanf("%d%d", &N, &K);
    if (K == 1) {
        printf("%d\n", N);
        return 0;
    }
    int ret = 0;
    unordered_map<vector<int>, int> m;
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
