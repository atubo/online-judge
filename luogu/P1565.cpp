// https://www.luogu.org/problem/show?pid=1565
// 牛宫

#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, int> PII;
typedef vector<int>::const_iterator Iter;

int64_t A[210][210], B[210];
int N, M;

bool comp(int i, int j) {
    return B[i] > B[j];
}

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
            vector<int> q;
            q.push_back(0);
            B[0] = 0;
            for (int k = 1; k <= M; k++) {
                int64_t s = A[j][k] - A[i-1][k];
                B[k] = s;
                Iter it = lower_bound(q.begin(), q.end(), k, comp);
                if (it != q.end()) {
                    ans = max(ans, (j-i+1) * (k-*it));
                }
                if (s < B[q.back()]) {
                    q.push_back(k);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
