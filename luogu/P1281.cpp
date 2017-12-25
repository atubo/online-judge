// https://www.luogu.org/problemnew/show/P1281
// 书的复制

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 510;
int M, K;
int64_t A[MAXM];

bool check(int64_t x) {
    int cnt = 1, curr = 0;
    for (int i = 0; i < M; i++) {
        if (curr + A[i] > x) {
            cnt++;
            curr = A[i];
        } else {
            curr += A[i];
        }
    }
    return cnt <= K;
}

void process(int64_t x) {
    using PII = pair<int, int>;
    vector<PII> ans;
    int end = M, curr = 0;
    for (int i = M-1; i >= 0; i--) {
        if (A[i] + curr > x) {
            ans.push_back(make_pair(i+2, end));
            end = i+1;
            curr = A[i];
        } else {
            curr += A[i];
        }
    }
    printf("1 %d\n", end);
    for (int i = (int)ans.size()-1; i >= 0; i--) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
}

int main() {
    scanf("%d%d", &M, &K);
    int64_t tot = 0, maxp = 0;
    for (int i = 0; i < M; i++) {
        scanf("%lld", &A[i]);
        tot += A[i];
        maxp = max(maxp, A[i]);
    }

    if (K == 0) return 0;

    int lo = maxp, hi = tot;
    if (check(lo)) {
        process(lo);
        return 0;
    }

    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else            lo = mid;
    }
    process(hi);

    return 0;
}
