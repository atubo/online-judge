// https://www.luogu.org/problem/show?pid=1308
// 统计单词数

#include <bits/stdc++.h>
using namespace std;

int main() {
    const char SPACE = ' ';
    string w, s;
    getline(cin, w);
    getline(cin, s);
    for (int i = 0; i < (int)w.length(); i++) {
        w[i] = tolower(w[i]);
    }
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    int p = 0;
    const int N = s.length();
    while (p < N && s[p] == SPACE) p++;
    if (p == N) {
        cout << "-1" << endl;
        return 0;
    }

    int ans = 0, pos = -1;

    while (p < N) {
        int q = p;
        while (q < N && s[q] != SPACE) q++;
        if (w == s.substr(p, q-p)) {
            ans++;
            if (pos == -1) pos = p;
        }
        p = q;
        while (p < N && s[p] == SPACE) p++;
    }

    if (ans == 0) {
        cout << "-1" << endl;
    } else {
        cout << ans << " " << pos << endl;
    }
    
    return 0;
}
