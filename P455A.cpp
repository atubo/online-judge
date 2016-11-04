// http://codeforces.com/problemset/problem/455/A
#include <bits/stdc++.h>

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        scanf("%d", &A[i]);\
    }

using namespace std;
using PII = pair<int, int>;

int64_t prod(const PII& p) {
    return int64_t(p.first) * p.second;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    READ_ARRAY(N, A);
    sort(A.begin(), A.end());
    vector<PII> B;
    int last = 0;
    for (int x: A) {
        if (x != last) {
            B.push_back(make_pair(x, 1));
            last = x;
        } else {
            B.back().second++;
        }
    }

    int M = B.size();
    vector<int64_t> dp(M), maxdp(M);
    dp[0] = maxdp[0] = prod(B[0]);
    for (int i = 1; i < M; i++) {
        int64_t incr = prod(B[i]);
        if (B[i-1].first < B[i].first - 1) {
            dp[i] = maxdp[i-1] + incr;
        } else {
            dp[i] = (i >= 2 ? maxdp[i-2] : 0) + incr;
        }
        maxdp[i] = max(maxdp[i-1], dp[i]);
    }

    cout << maxdp[M-1] << endl;
    return 0;
}
