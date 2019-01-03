// https://www.luogu.org/problemnew/show/P4109
// [HEOI2015]定价

#include <bits/stdc++.h>
using namespace std;

int T;
int L, R;
int64_t p10[12];

int score(int x) {
    string s = to_string(x);
    while (s.back() == '0') s.pop_back();
    int l = s.length();
    if (s.back() == '5') return 2*l-1;
    return 2*l;
}

int pick(int x1, int x2) {
    int s1 = score(x1);
    int s2 = score(x2);
    if (s1 < s2) return x1;
    if (s1 > s2) return x2;
    return min(x1, x2);
}

int solve(int l, int r) {
    if (l == r) return l;
    string s1 = to_string(l);
    string s2 = to_string(r);
    assert(s1.length() == s2.length());
    const int len = s1.length();
    int pos = 0;
    while (pos < len && s1[pos] == s2[pos]) pos++;
    assert(pos < len);
    int p;
    if (pos == len-1 || stoi(s1.substr(pos+1)) == 0) {
        p = s1[pos] - '0';
    } else {
        p = s1[pos] - '0' + 1;
    }
    int q = s2[pos] - '0';
    int x;
    if ((p > 0 && p <= 5) && 5 <= q) x = 5;
    else x = p;
    string s = s1.substr(0, pos) + char('0'+x) + string(len-pos-1, '0');
    return stoi(s);
}


int solve() {
    scanf("%d%d", &L, &R);
    string s1 = to_string(L);
    string s2 = to_string(R);
    int l1 = s1.length();
    int l2 = s2.length();
    if (l2 > l1) {
        int64_t x = p10[s1.length()+1];
        int r = x-1;
        if (stoi(s2.substr(0, l2-l1)) >= 5) x = 5*x;
        return pick(x, solve(L, r));
    }
    return solve(L, R);
}

int main() {
    p10[1] = 1;
    for (int i = 2; i < 12; i++) p10[i] = p10[i-1]*10;

    scanf("%d", &T);
    while (T--) {
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}
