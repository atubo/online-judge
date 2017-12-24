// https://www.luogu.org/problemnew/show/P1941
// 飞扬的小鸟

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 10010, MAXM = 2010;
int N, M, K;
int X[MAXN], Y[MAXN];
vector<int> dp(MAXM), tmp(MAXM);

struct Pipe {
    Pipe(): L(-1), H(-1) {}
    int L, H;
} pipes[MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }
    for (int i = 0; i < K; i++) {
        int P, L, H;
        scanf("%d%d%d", &P, &L, &H);
        pipes[P].L = L;
        pipes[P].H = H;
    }

    dp[0] = INF;
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        int x = X[i-1], y = Y[i-1];
        for (int j = 0; j <= x ; j++) tmp[j] = INF;
        for (int j = x+1; j <= M+x; j++) {
            tmp[j] = min(tmp[j-x], dp[j-x]) + 1;
        }
        for (int j = M+1; j <= M+x; j++) tmp[M] = min(tmp[M], tmp[j]);
        for (int j = 0; j <= M - y; j++) {
            tmp[j] = min(tmp[j], dp[j+y]);
        }
        bool hasPipe = (pipes[i].L >= 0);
        bool canPass = false;
        for (int j = 1; j <= M; j++) {
            bool blocked = (hasPipe && (j <= pipes[i].L || j >= pipes[i].H));
            tmp[j] = (blocked ? INF : tmp[j]);
            if (hasPipe && tmp[j] < INF) canPass = true;
        }
        ret += canPass;
        swap(dp, tmp);
#if 0
        printf("%2d: ", i);
        for (int k = 1; k <= M; k++) {
            if (dp[k] >= INF) printf("INF ");
            else printf("%3d ", dp[k]);
        }
        printf("\n");
#endif
    }

    if (ret < K) {
        printf("0\n");
        printf("%d\n", ret);
    } else {
        printf("1\n");
        int ans = INT_MAX;
        for (int i = 1; i <= M; i++) {
            ans = min(ans, dp[i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
