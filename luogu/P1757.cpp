// https://www.luogu.org/problemnew/show/P1757
// 通天之分组背包

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int M, N;
struct Item {
    int a, b, c;
    bool operator < (const Item &other) const {
        if (c < other.c) return true;
        if (c > other.c) return false;
        if (a < other.a) return true;
        if (a > other.a) return false;
        return b < other.b;
    }
} items[MAXN];

vector<int64_t> dp(MAXN), dp_next(MAXN);

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < N; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        items[i] = {a, b, c};
    }
    sort(items, items+N);
    int p = 0;
    while (p < N) {
        int q = p;
        while (items[q].c == items[p].c) {
            int a = items[q].a;
            int b = items[q].b;
            for (int i = M; i >= 0; i--) {
                dp_next[i] = max(dp_next[i], dp[i]);
                if (i >= a) {
                    dp_next[i] = max(dp_next[i], dp[i-a] + b);
                }
            }
            q++;
        }
        swap(dp, dp_next);
        p = q;
    }

    printf("%ld", dp[M]);
    return 0;
}
