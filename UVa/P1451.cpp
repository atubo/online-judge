// 1451 - Average

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
char s[MAXN];
int ps[MAXN], q[MAXN];
int N, L;

int slopeCmp(int x1, int x2, int x3, int x4) {
    return (ps[x2] - ps[x1]) * (x4 - x3) - (ps[x4] - ps[x3]) * (x2 - x1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %s", &N, &L, s+1);
        for (int i = 1; i <= N; i++) {
            ps[i] = ps[i-1] + s[i] - '0';
        }
        int i = 0, j = 0;

        int ansL = 0, ansR = L;
        for (int t = L; t <= N; t++) {
            while (j > i + 1 && slopeCmp(q[j-2], q[j-1], q[j-1], t-L) >= 0) j--;
            q[j++] = t-L;
            while (j > i + 1 && slopeCmp(q[i], t, q[i+1], t) <= 0) i++;
            int c = slopeCmp(q[i], t, ansL, ansR);
            if (c > 0 || (c == 0 && t - q[i] < ansR - ansL)) {
                ansL = q[i];
                ansR = t;
            }
        }
        printf("%d %d\n", ansL+1, ansR);
    }
    return 0;
}
