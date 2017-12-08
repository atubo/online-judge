// https://www.luogu.org/problemnew/show/P3938
// 斐波那契

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 60;
vector<int64_t> ps(MAXN);

int64_t father(int64_t x) {
    assert(x > 0);
    if (x <= 2) return x - 1;
    return x - *(lower_bound(ps.begin(), ps.end(), x) - 1);
}

stack<int64_t> ancestors(int64_t x) {
    stack<int64_t> ret;
    int64_t fa = x;
    while (fa) {
        ret.push(fa);
        fa = father(fa);
    }
    return ret;
}

int64_t lca(stack<int64_t>& sa, stack<int64_t>& sb) {
    int64_t ret = 1;
    while (!sa.empty() && !sb.empty() && sa.top() == sb.top()) {
        ret = sa.top();
        sa.pop();
        sb.pop();
    }
    return ret;
}

int main() {
    vector<int64_t> F(MAXN);
    F[0] = F[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        F[i] = F[i-2] + F[i-1];
    }
    partial_sum(F.begin(), F.end(), ps.begin());
    for (int i = 0; i < MAXN; i++) ps[i]++;

    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int64_t a, b;
        scanf("%lld%lld", &a, &b);
        stack<int64_t> sa = ancestors(a);
        stack<int64_t> sb = ancestors(b);
        printf("%lld\n", lca(sa, sb));
    }

    return 0;
}

