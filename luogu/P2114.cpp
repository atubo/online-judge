// https://www.luogu.org/problemnew/show/P2114
// 起床困难综合症

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int N, M;
vector<PII> ops;

int calc(int x, int d) {
    // x is 0/1, d is bit position
    for (const PII &op: ops) {
        int y = (op.second >> d);
        if (op.first == 0) x = x | y;
        else if (op.first == 1) x = x ^ y;
        else x = x & y;
    }
    return x;
}

int ret;
void dp(int d, bool clamped) {
    if (d == -1) return;
    int y0 = calc(0, d);
    if (!clamped || (M & (1 << d))) {
        int y1 = calc(1, d);
        if (y1 > y0) {
            ret = ret | (1 << d);
            dp(d-1, clamped);
        } else {
            dp(d-1, false);
        }
    } else {
        dp(d-1, true);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        char cmd[10];
        int c, t;
        scanf("%s%d", cmd, &t);
        if (cmd[0] == 'O') c = 0;
        else if (cmd[0] == 'X') c = 1;
        else c = 2;
        ops.push_back(make_pair(c, t));
    }
    dp(30, true);
    for (const PII &op: ops) {
        int y = op.second;
        if (op.first == 0) ret |= y;
        else if (op.first == 1) ret ^= y;
        else ret &= y;
    }

    printf("%d\n", ret);

    return 0;
}

