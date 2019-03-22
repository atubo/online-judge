// https://www.luogu.org/problemnew/show/P4591
// [TJOI2018]碱基序列

#include <bits/stdc++.h>
using namespace std;

class KMP {
public:
    KMP(const string& str):f(str.length(), 0) {
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)str.length(); s++) {
            while (t > 0 && str[s] != str[t]) {
                t = f[t-1];
            }
            if (str[s] == str[t]) {
                t++;
            }
            f[s] = t;
        }
    }

    int operator[](int i) const {
        return f[i];
    }

private:
    vector<int> f;
};

const int MOD = 1e9+7;
int K;
int dp[101][10010];

struct Amino {
    int a;
    vector<string> base;
} aminos[101];

void process(const string &s, const string &b, int idx) {
    KMP kmp(b);
    const int m = b.length();
    int t = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        while (t > 0 && s[i] != b[t]) {
            t = kmp[t-1];
        }
        if (s[i] == b[t]) t++;
        if (t == m) {
            t = kmp[t-1];
            (dp[idx][i-m+1] += dp[idx+1][i+1]) %= MOD;
        }
    }
}

int main() {
    scanf("%d", &K);
    string s;
    cin >> s;

    int totbase = 0;
    for (int i = 0; i < K; i++) {
        int a;
        scanf("%d", &a);
        aminos[i].a = a;
        aminos[i].base.resize(a);
        for (int j = 0; j < a; j++) {
            cin >> aminos[i].base[j];
        }
        totbase += a;
    }

    for (int i = 0; i <= (int)s.length(); i++) {
        dp[K][i] = 1;
    }
    for (int i = K-1; i >= 0; i--) {
        for (int j = 0; j < aminos[i].a; j++) {
            process(s, aminos[i].base[j], i);
        }
    }

    int ans = 0;
    for (int i = 0; i <= (int)s.length(); i++) {
        (ans += dp[0][i]) %= MOD;
    }
    printf("%d\n", ans);

    return 0;
}
