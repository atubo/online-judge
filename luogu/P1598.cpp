// https://www.luogu.org/problem/show?pid=1598
// 垂直柱状图

#include <bits/stdc++.h>
using namespace std;

int main() {
    int cnt[26] = {0};
    for (int i = 0; i < 4; i++) {
        string s;
        getline(cin, s);
        for (char c: s) {
            if (c < 'A' || c > 'Z') continue;
            cnt[c-'A']++;
        }
    }

    int maxcnt = 0;
    for (int i = 0; i < 26; i++) {
        maxcnt = max(maxcnt, cnt[i]);
    }

    for (int r = maxcnt; r >= 1; r--) {
        string s(53, ' ');
        for (int i = 0; i < 26; i++) {
            if (cnt[i] >= r) s[i*2] = '*';
        }
        cout << s << endl;
    }
    string s(53, ' ');
    for (int i = 0; i < 26; i++) {
        s[2*i] = 'A' + i;
    }
    cout << s << endl;
    return 0;
}
