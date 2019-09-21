// https://www.luogu.org/problem/P3615
// 如厕计划

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100010;
int64_t N;
int M;

struct Line {
    string s;
    int64_t k;
} L[MAXM];

int main() {
    scanf("%ld%d", &N, &M);
    for (int i = 0; i < M; i++) {
        cin >> L[i].s >> L[i].k;
    }
    int64_t mn = 0, end = 0;
    for (int i = M-1; i >= 0; i--) {
        int l = L[i].s.length();
        int64_t cnt = 0, lm = 0;
        for (int j = l-1; j >= 0; j--) {
            cnt += (L[i].s[j] == 'M' ? -1 : 1);
            lm = min(lm, cnt);
        }
        if (lm < 0) {
            if (cnt > 0) mn = min(mn, end + lm);
            else mn = min(mn, end + cnt*(L[i].k-1) + lm);
        }
        end += cnt * L[i].k;
    }
    if (end >= 0) {
        int64_t ans = (mn < -1 ? -mn-1 : 0);
        printf("%ld", ans);
    } else {
        printf("-1\n");
    }

    return 0;
}
