// http://acm.hdu.edu.cn/showproblem.php?pid=3530
// Subsequence

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int A[MAXN];

int main() {
    int N, M, K;
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        deque<int> maxq, minq;
        int ans = (M == 0);
        maxq.push_back(0);
        minq.push_back(0);
        int last = -1;
        for (int i = 1; i < N; i++) {
            while (maxq.size() > 0 && A[maxq.back()] <= A[i]) maxq.pop_back();
            maxq.push_back(i);
            while (minq.size() > 0 && A[minq.back()] >= A[i]) minq.pop_back();
            minq.push_back(i);

            while (A[maxq.front()] - A[minq.front()] > K) {
                if (maxq.front() < minq.front()) {
                    last = maxq.front();
                    maxq.pop_front();
                }
                else {
                    last = minq.front();
                    minq.pop_front();
                }
            }
            if (A[maxq.front()] - A[minq.front()] >= M) {
                ans = max(ans, i - last);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
