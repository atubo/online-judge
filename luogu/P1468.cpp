// https://www.luogu.org/problem/show?pid=1468
// 派对灯 Party Lamps

#include <bits/stdc++.h>
using namespace std;

int N, C;
int mask, kn;

void sortUniq(vector<int> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        v[i] = v[i] % 6;
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

bool convert(vector<int> &on, vector<int> &off) {
    sortUniq(on);
    sortUniq(off);

    int koff = 0;
    for (int d: on) {
        mask |= (1 << d);
        kn |= (1 << d);
    }
    for (int d: off) {
        mask |= (1 << d);
        koff |= (1 << d);
    }
    return (kn & koff) == 0;
}

bool dp[10010][64];

string toString(int k) {
    string s(N, '0');
    for (int d = 0; d < 6; d++) {
        if ((k >> d) & 1) {
            for (int p = d; p < N; p += 6) {
                s[p] = '1';
            }
        }
    }
    return s;
}

int main() {
    scanf("%d%d", &N, &C);
    vector<int> on, off;
    int x;
    while (scanf("%d", &x) && x != -1) {
        on.push_back(x-1);
    }
    while (scanf("%d", &x) && x != -1) {
        off.push_back(x-1);
    }

    if (!convert(on, off)) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    dp[0][63] = true;
    for (int i = 0; i < C; i++) {
        for (int k = 0; k < 64; k++) {
            dp[i+1][k^63] |= dp[i][k];
            dp[i+1][k^42] |= dp[i][k];
            dp[i+1][k^21] |= dp[i][k];
            dp[i+1][k^9] |= dp[i][k];
        }
    }

    vector<string> ans;
    for (int k = 0; k < 64; k++) {
        if ((dp[C][k]) && ((k & mask) == kn)) {
            ans.push_back(toString(k));
        }
    }

    sort(ans.begin(), ans.end());
    if (!ans.empty()) {
        for (const string &s: ans) {
            printf("%s\n", s.c_str());
        }
    } else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}
