// https://www.luogu.org/problemnew/show/P2887
// [USACO07NOV]防晒霜Sunscreen

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2510;
int C, L;
int F[MAXN];

int main() {
    vector<vector<int>> R(1001);
    scanf("%d%d", &C, &L);
    for (int i = 0; i < C; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        R[x].push_back(y);
    }
    vector<vector<int>> S(1001);
    for (int i = 0; i < L; i++) {
        int s, c;
        scanf("%d%d", &s, &c);
        S[s].push_back(c);
    }

    int ans = 0;
    for (int i = 0; i <= 1000; i++) {
        for (int x: R[i]) {
            F[x]++;
        }
        for (int c: S[i]) {
            for (int j = i; j <= 1000; j++) {
                if (c > F[j]) {
                    ans += F[j];
                    c -= F[j];
                    F[j] = 0;
                } else {
                    ans += c;
                    F[j] -= c;
                    c = 0;
                    break;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
