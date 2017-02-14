// https://www.luogu.org/problem/show?pid=1541
// 乌龟棋
#include <bits/stdc++.h>
using namespace std;

int dp[41][41][41][41];
int N, M;
int A[360];
int cards[4];

struct Tuple {
    Tuple(int a_, int b_, int c_, int d_): a(a_), b(b_), c(c_), d(d_) {}
    int a, b, c, d;
};

int pos(int a, int b, int c, int d) {
    return a + 2*b + 3*c + 4*d;
}

void update(int a, int b, int c, int d,
            int a2, int b2, int c2, int d2, int step,
            queue<Tuple>& q) {
    if (dp[a2][b2][c2][d2] == -1) {
        q.push(Tuple(a2, b2, c2, d2));
    }
    dp[a2][b2][c2][d2] = max(dp[a2][b2][c2][d2],
                             dp[a][b][c][d] + A[pos(a, b, c, d) + step]);
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < M; i++) {
        int b;
        scanf("%d", &b);
        cards[b-1]++;
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0][0] = A[0];
    queue<Tuple> q;
    q.push(Tuple(0, 0, 0, 0));
    while (!q.empty()) {
        Tuple t = q.front();
        int a = t.a, b = t.b, c = t.c, d = t.d;
        q.pop();
        if (a < cards[0]) {
            update(a, b, c, d, a+1, b, c, d, 1, q);
        }
        if (b < cards[1]) {
            update(a, b, c, d, a, b+1, c, d, 2, q);
        }
        if (c < cards[2]) {
            update(a, b, c, d, a, b, c+1, d, 3, q);
        }
        if (d < cards[3]) {
            update(a, b, c, d, a, b, c, d+1, 4, q);
        }
    }

    printf("%d\n", dp[cards[0]][cards[1]][cards[2]][cards[3]]);
    return 0;
}
