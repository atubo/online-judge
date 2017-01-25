// http://acm.hdu.edu.cn/showproblem.php?pid=2993
// MAX Average Problem

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int N, K;
int S[MAXN], q[MAXN];

int direction(int k, int j, int i) {
    int64_t x1 = j - k, y1 = S[j] - S[k];
    int64_t x2 = i - j, y2 = S[i] - S[j];
    int64_t cross = x1 * y2 - x2 * y1;
    return (cross > 0 ? 1 : (cross < 0 ? -1 : 0));
}

double calcMaxSlope(int k) {
    double ans = 0;
    int head = 0, tail = 0;
    for (int i = 0; i <= N-k; i++) {
        int j = i + k;
        while (tail - head > 1 && direction(q[tail-2], q[tail-1], i) != 1) {
            tail--;
        }
        q[tail++] = i;

        while (tail - head > 1 && direction(q[head], q[head+1], j) != -1) {
            head++;
        }
        int l = q[head];
        ans = max(ans, double(S[j]-S[l])/(j-l));
    }
    return ans;
}


int main() {
    while (scanf("%d %d", &N, &K) == 2) {
        for (int i = 1; i <= N; i++) {
            scanf("%d", &S[i]);
            S[i] += S[i-1];
        }

        double maxSlope = calcMaxSlope(K);
        printf("%.2f\n", maxSlope);
    }
    return 0;
}
