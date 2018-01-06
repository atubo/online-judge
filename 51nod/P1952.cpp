// https://www.51nod.com/onlineJudge/questionCode.html#!problemId=1952
// 栈

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;
const int MOD_CONST = 1e9+7;

int ans;
void add(int x) {
    ans = (ans + x) % MOD_CONST;
}

void print(const deque<PII> &dq) {
    for (const PII &p: dq) {
        printf("(%d %d) ", p.first, p.second);
    }
}

int main() {
    int64_t n, A, B, C, x, a, b, MOD;
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &n, &A, &B, &C, &x, &a, &b, &MOD);
    int m = 0, top = 0, bot = -1;
    deque<PII> dq;
    for (int i = 1; i <= n; i++) {
        int p, q;
        x = (x * a + b) % MOD;
        int r = x % (A + B + C);
        if (r < A || m <= 1) {
            p = 0;
            q = x;
            m++;
        } else if (A <= r && r < A + B) {
            p = 1;
            q = x;
            m++;
        } else {
            p = 2;
            m--;
        }
        //printf("%d %d\n", p, q);
        if (p == 0) {
            if (dq.empty() || q > dq.back().second) {
                dq.push_back(make_pair(top, q));
            }
            top++;
            //print(dq);
            //printf(" top=%d bot=%d\n", top, bot);
            //printf("%d\n", dq.back().second);
            add(dq.back().second);
        } else if (p == 1) {
            while (!dq.empty() && dq.front().second <= q) {
                dq.pop_front();
            }
            dq.push_front(make_pair(bot, q));
            bot--;
            //print(dq);
            //printf(" top=%d bot=%d\n", top, bot);
            //printf("%d\n", dq.back().second);
            add(dq.back().second);
        } else {
            top--;
            if (top == dq.back().first) {
                dq.pop_back();
            }
            //print(dq);
            //printf(" top=%d bot=%d\n", top, bot);
            //printf("%d\n", dq.back().second);
            add(dq.back().second);
        }
    }

    printf("%d\n", ans);
    return 0;
}
