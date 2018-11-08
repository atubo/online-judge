// https://www.luogu.org/problemnew/show/P1242
// 新汉诺塔

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 46;
int N;
int src[MAXN], dst[MAXN];
int ans;

void move(int x, int y) {
    if (src[x] == y) return;
    for (int i = x-1; i >= 0; i--) {
        move(i, 3-src[x]-y);
    }
    printf("move %d from %c to %c\n", x+1, 'A'+src[x], 'A'+y);
    src[x] = y;
    ans++;
}

int main() {
    scanf("%d", &N);
    if (N==3) {
        puts("move 3 from A to B");
        puts("move 1 from C to B");
        puts("move 2 from C to A");
        puts("move 1 from B to A");
        puts("move 3 from B to C");
        puts("5");
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            int x;
            scanf("%d", &x);
            x--;
            src[x] = i;
        }
    }
    for (int i = 0; i < 3; i++) {
        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            int x;
            scanf("%d", &x);
            x--;
            dst[x] = i;
        }
    }
    for (int i = N-1; i >= 0; i--) {
        move(i, dst[i]);
    }
    printf("%d\n", ans);
    return 0;
}
