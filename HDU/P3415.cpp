// http://acm.hdu.edu.cn/showproblem.php?pid=3415
// Max Sum of Max-K-sub-sequence

#include <bits/stdc++.h>
using namespace std;

const int MAXSZ = 200010;
int A[MAXSZ], ps[MAXSZ];
int N, K;

void solve() {
    scanf("%d %d", &N, &K);
    for (int i = N; i >= 1; i--) {
        scanf("%d", &A[i]);
        A[i+N] = A[i];
    }

    partial_sum(A, A+2*N+1, ps);
    deque<int> q;
    int ans = INT_MIN, left, right;
    q.push_back(0);
    for (int i = 1; i <= N+N; i++) {
        while (i - q.front() > K) q.pop_front();
        if (ps[i] - ps[q.front()] >= ans) {
            ans = ps[i] - ps[q.front()];
            left = q.front() + 1;
            left = (left-1) % N + 1;
            right = (i-1) % N + 1;
        }
        while (!q.empty() && ps[q.back()] >= ps[i]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    printf("%d %d %d\n", ans, N+1-right, N+1-left);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
