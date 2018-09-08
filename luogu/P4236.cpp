// https://www.luogu.org/problemnew/show/P4236
// 扑克

#include <bits/stdc++.h>
using namespace std;

int Q;
int A;

bool solve() {
    string s;
    cin >> A >> s;
    int r = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        r = (r*10 + s[i]-'0') % (A+1);
    }
    int r2 = (s.back()-'0') & 1;
    if (A & 1) return r2 == 1;
    else return ((r == A) || (r & 1));
}

int main() {
    scanf("%d", &Q);
    while (Q--) {
        bool ok = solve();
        if (ok) {
            printf("lsq Win\n");
        } else {
            printf("wzt Win\n");
        }
    }
    return 0;
}
