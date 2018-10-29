// https://www.luogu.org/problemnew/show/P1415
// 拆分数列

#include <bits/stdc++.h>
using namespace std;

struct Number {
    string s;
    int start, end;
    bool operator < (const Number &other) const {
        if (s.length() < other.s.length()) return true;
        if (s.length() > other.s.length()) return false;
        return s < other.s;
    }

    bool equal(const Number &other) const {
        return s == other.s;
    }
};

Number canon(const string &s, int p, int q) {
    int i = p;
    while (i < q && s[i] == '0') i++;
    return {s.substr(i, q-i+1), p, q};
}

int main() {
    string s;
    cin >> s;
    const int N = s.length();
    vector<Number> dp(N);
    for (int i = 0; i < N; i++) {
        dp[i] = canon(s, 0, i);
        for (int j = 0; j < i; j++) {
            Number tail = canon(s, j+1, i);
            if (dp[j] < tail) dp[i] = tail;
        }
    }

    vector<Number> dp2(N);
    int last = dp[N-1].start;
    dp2[last] = dp[N-1];
    for (int i = last-1; i >= 0; i--) {
        auto x = canon(s, i, N-1);
        if (x.equal(dp[N-1])) {
            dp2[i] = x;
            continue;
        }
        for (int j = i+1; j <= last; j++) {
            x = canon(s, i, j-1);
            if (!(x < dp[N-1])) break;
            if (x < dp2[j]) dp2[i] = x;
        }
    }

    int p = 0;
    while (true) {
        int b = dp2[p].start, e = dp2[p].end;
        printf("%s", s.substr(b, e-b+1).c_str());
        if (e == N-1) break;
        printf(",");
        p = e + 1;
    }

    return 0;
}
