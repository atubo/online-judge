// https://www.luogu.org/problemnew/show/P2519
// [HAOI2011]problem a

#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;

struct Interval {
    int l, r, cnt;
    bool operator < (const Interval &other) {
        if (r < other.r) return true;
        if (r > other.r) return false;
        return l < other.l;
    }
};

const int MAXN = 100010;
int dp[MAXN];
int N;

int main() {
    scanf("%d", &N);
    map<Pii, int> pairCnt;
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a + b > N-1) {
            continue;
        }
        pairCnt[make_pair(a, b)]++;
    }
    vector<Interval> intervals;
    for (auto p: pairCnt) {
        int a = p.first.first;
        int b = p.first.second;
        intervals.push_back({b+1, N-a, min(N-a-b, p.second)});
    }
    sort(intervals.begin(), intervals.end());
    int p = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i-1];
        while (p < (int)intervals.size() && intervals[p].r == i) {
            const auto & itv = intervals[p];
            dp[i] = max(dp[i], dp[itv.l-1] + itv.cnt);
            p++;
        }
    }
    printf("%d\n", N-dp[N]);
    return 0;
}
