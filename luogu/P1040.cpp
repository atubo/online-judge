// https://www.luogu.org/problem/show?pid=1040
// 加分二叉树

#include <bits/stdc++.h>
using namespace std;

typedef pair<unsigned int, unsigned int> PII;
const int MAXN = 32;
PII dp[MAXN][MAXN];
unsigned int A[MAXN];
int N;

unsigned int score(int i, int k, int j) {
    if (k == i) {
        return dp[k+1][j].second + A[k];
    }
    if (k == j) {
        return dp[i][k-1].second + A[k];
    }
    return dp[i][k-1].second * dp[k+1][j].second + A[k];
}

void traverse(int p, int q) {
    int k = dp[p][q].first;
    cout << k+1 << " ";
    if (k > p) traverse(p, k-1);
    if (k < q) traverse(k+1, q);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        dp[i][i] = make_pair(i, A[i]);
    }

    for (int L = 2; L <= N; L++) {
        for (int i = 0; i <= N - L; i++) {
            unsigned int maxv = 0, maxp = 0;
            int j = i + L - 1;
            for (int k = i; k <= j; k++) {
                unsigned int s = score(i, k, j);
                if (s > maxv) {
                    maxv = s;
                    maxp = k;
                }
            }
            dp[i][j] = make_pair(maxp, maxv);
        }
    }

    cout << dp[0][N-1].second << endl;
    traverse(0, N-1);
    return 0;
}
