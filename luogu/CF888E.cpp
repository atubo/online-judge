// https://www.luogu.org/problemnew/show/CF888E
// Maximum Subsequence

#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[36];

void dfs(int64_t x, int p, int q, vector<int> &ret) {
    if (p > q) {
        ret.push_back(x%M);
        return;
    }
    dfs(x, p+1, q, ret);
    dfs(x+A[p], p+1, q, ret);
}

vector<int> build(int p, int q) {
    vector<int> ret;
    if (p > q) return ret;
    dfs(0, p, q, ret);
    return ret;
}

void normalize(vector<int>& b) {
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
}

int solve(const vector<int>& b1, const vector<int> &b20) {
    auto b2 = b20;
    for (int i = 0; i < (int)b20.size(); i++) {
        b2.push_back(b20[i] + M);
    }

    int ans = 0;
    for (int x1: b1) {
        int r = M -1 - x1;
        auto it = lower_bound(b2.begin(), b2.end(), r);
        ans = max(ans, (x1 + *it) % M);
        if (it != b2.begin()) {
            ans = max(ans, (x1 + *(--it)) % M);
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i] %= M;
    }
    if (N == 1) {
        printf("%d", A[0] % M);
        return 0;
    }
    auto b1 = build(0, (N-1)/2);
    auto b2 = build((N-1)/2+1, N-1);

    normalize(b1);
    normalize(b2);

    int ans = solve(b1, b2);
    printf("%d", ans);
    return 0;
}
