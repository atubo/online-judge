// https://www.luogu.org/problemnew/show/P2215
// [HAOI2007]上升序列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int N, M;
int A[MAXN], B[MAXN];
int Q;

int id(int x) {
    return lower_bound(B, B+M, x) - B;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        B[i-1] = A[i];
    }
    sort(B, B+N);
    M = unique(B, B+N) - B;
    for (int i = 1; i <= N; i++) {
        A[i] = id(A[i]);
    }

    vector<int> length(N+1);
    vector<int> dp(N+1, -1);
    dp[0] = INT_MAX;
    for (int i = N; i >= 1; i--) {
        int x = lower_bound(dp.begin(), dp.end(), A[i], greater<int>())
            - dp.begin();
        length[i] = x;
        dp[x] = max(dp[x], A[i]);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int L;
        scanf("%d", &L);

        int x = -1;
        vector<int> ret;
        for (int j = 1; j <= N; j++) {
            if ((x < A[j]) && length[j] >= L) {
                ret.push_back(A[j]);
                x = A[j];
                L--;
                if (L == 0) break;
            }
        }
        if (ret.empty()) {
            printf("Impossible\n");
        } else {
            for (int r: ret) {
                printf("%d ", B[r]);
            }
            printf("\n");
        }
    }

    return 0;
}
