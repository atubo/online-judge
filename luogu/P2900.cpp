// https://www.luogu.org/problem/show?pid=2900
// [USACO08MAR]土地征用Land Acquisition

#include <bits/stdc++.h>
using namespace std;


const int MAXN = 50010;
int64_t A[MAXN];

namespace ConvextHullTrick {

    int64_t C[MAXN];    // save input array here
    int64_t S[MAXN];
    int64_t dp[MAXN];
    int N;

    int64_t Y(int i) {
        return dp[i];
    }

    int64_t X(int i) {
        return -A[i];
    }

    int64_t numer(int k, int j) {
        return Y(j) - Y(k);
    }

    int64_t denom(int k, int j) {
        return X(j) - X(k);
    }

    bool isConvex(int a, int b, int c) {
        return numer(a, b) * denom(b, c) < numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        return dp[j] + A[j] * S[i];
    }

    void runDp() {
        // initialize N and S

        dp[0] = 0;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= N; i++) {
            // it may make sense to skip 0 elements
            // if that's the case, un-comment the following
            /*
            if (S[i] == S[i-1]) {
                dp[i] = dp[i-1];
                continue;
            }
            */
            while (q.size() > 1 && numer(q[0], q[1]) <= denom(q[0], q[1]) * S[i]) {
                q.pop_front();
            }

            dp[i] = getDp(i, q.front());
            while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
                q.pop_back();
            }
            q.push_back(i);
        }
    }
}

struct Land {
    int w, l;
    bool operator > (const Land &other) const {
        if (w > other.w) return true;
        if (w < other.w) return false;
        return l > other.l;
    }
} lands[MAXN];

const int INF = 2e6;
int N;

int main() {
    namespace CH = ConvextHullTrick;
    scanf("%d", &N);
    lands[0] = {INF, 0};
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &lands[i].w, &lands[i].l);
    }
    sort(lands, lands+N+1, greater<Land>());
    vector<Land> filtered;
    filtered.push_back(lands[0]);
    for (int i = 1; i <= N; i++) {
        if (lands[i].l > filtered.back().l) {
            filtered.push_back(lands[i]);
        }
    }
    int n = filtered.size();
    CH::N = n + 1;
    for (int i = 0; i < n-1; i++) {
        A[i] = filtered[i+1].w;
        CH::S[i] = filtered[i].l;
    }
    CH::S[n-1] = filtered[n-1].l;
    CH::runDp();
    printf("%lld", CH::dp[n-1]);
    return 0;
}
