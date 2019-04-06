// https://www.luogu.org/problemnew/show/P1461
// 海明码 Hamming Codes

#include <bits/stdc++.h>
using namespace std;

int N, B, D;

int dist(int x, const vector<int> &a, int mx) {
    int ret = INT_MAX;
    for (int y: a) {
        int t = __builtin_popcount(x^y);
        if (t < mx) return t;
        ret = min(ret, t);
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &N, &B, &D);
    vector<int> ans(2);
    ans[0] = 0;
    ans[1] = (1<<D) - 1;
    int d = D;
    int n = 2;
    while ((int)ans.size() < N) {
        int mx = 0;
        int xmax = 0;
        for (int x = 1; x < (1<<d)-1; x++) {
            int h = dist(x, ans, mx);
            if (h > mx) {
                mx = h;
                xmax = x;
            }
        }
        int mask = ((1<<(D-mx))-1)<<d;
        for (int i = 0; i < n; i++) {
            ans.push_back(mask | (ans[i] ^ xmax));
        }
        d += D-mx;
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
        if ((i+1)%10 == 0) printf("\n");
    }

    return 0;
}
