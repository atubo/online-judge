// https://www.luogu.org/problem/show?pid=1565
// 牛宫

#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, int> PII;
typedef vector<PII>::const_iterator Iter;

int64_t A[210][210];
int N, M;

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%lld", &A[i][j]);
            A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            vector<PII> q;
            q.push_back(make_pair((int64_t)0, 0));
            for (int k = 1; k <= M; k++) {
                int64_t s = A[j][k] - A[i-1][k];
                Iter it = lower_bound(q.begin(), q.end(), make_pair(s, k),
                                      greater<PII>());
                if (it != q.end()) {
                    ans = max(ans, (j-i+1) * (k-it->second));
                }
                if (s < q.back().first) {
                    q.push_back(make_pair(s, k));
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
