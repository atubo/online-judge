// https://www.luogu.org/problemnew/show/P4279
// [SHOI2008]小约翰的游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
int T;
int N;
int A[MAXN];

void solve() {
    scanf("%d", &N);
    int nim = 0;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        nim ^= x;
        if (x > 1) cnt++;
    }
    if ((nim == 0 && cnt == 0) || (nim > 0 && cnt > 0)) {
        printf("John\n");
    } else {
        printf("Brother\n");
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
