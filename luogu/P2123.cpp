// https://www.luogu.org/problemnew/show/P2123
// 皇后游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
int T;
int N;
int A[MAXN], B[MAXN];

struct Minister {
    int a, b;
};

struct Cmp1 {
    bool operator()(const Minister &m1, const Minister &m2) const {
        return m1.a < m2.a;
    }
};

struct Cmp2 {
    bool operator()(const Minister &m1, const Minister &m2) const {
        return m1.b > m2.b;
    }
};

int main() {
    scanf("%d", &T);
    while (T--) {
        vector<Minister> m1, m2;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a <= b) m1.push_back({a, b});
            else m2.push_back({a, b});
        }
        sort(m1.begin(), m1.end(), Cmp1());
        sort(m2.begin(), m2.end(), Cmp2());
        int64_t ans = 0, tota = 0;
        for (const auto m: m1) {
            tota += m.a;
            ans = max(ans, tota) + m.b;
        }
        for (const auto m: m2) {
            tota += m.a;
            ans = max(ans, tota) + m.b;
        }
        printf("%ld\n", ans);
    }
    return 0;
}
