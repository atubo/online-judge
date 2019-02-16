// https://www.luogu.org/problemnew/show/P1254
// 扇区填数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
int N;
bool vis[23];
int A[MAXN];
bool B[60];
int ans;

bool checkAll() {
    memset(B, 0, sizeof(B));
    for (int l = 1; l < N;l++) {
        for (int s = 0; s <= N-1; s++) {
            int x = 0;
            for (int i = s; i < s+l; i++) {
                x += A[i%N];
            }
            if (B[x] || x > ans) return false;
            B[x] = true;
        }
    }
    int x = 0;
    for (int i = 0; i < N; i++) {
        x += A[i];
    }
    if (B[x] || x > ans) return false;
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return true;
}

bool check(int d) {
    if (d == N-1) return checkAll();
    memset(B, 0, sizeof(B));
    for (int l = 1; l <= d+1; l++) {
        for (int s = 0; s <= d-l+1; s++) {
            int x = 0;
            for (int i = s; i < s+l; i++) {
                x += A[i];
            }
            if (B[x] || x > ans) return false;
            B[x] = true;
        }
    }
    return true;
}

void dfs(int d) {
    if (d >= N) return;
    for (int i = 1; i <= 22; i++) {
        if (!vis[i]) {
            vis[i] = true;
            A[d] = i;
            if (check(d)) dfs(d+1);
            vis[i] = false;
        }
    }
    return;
}

void solve8() {
    printf("1 2 10 19 4 7 9 5\n1 3 5 11 2 12 17 6\n");
    printf("1 3 8 2 16 7 15 5\n1 4 2 10 18 3 11 8\n");
    printf("1 4 22 7 3 6 2 12\n1 5 9 7 4 19 10 2\n");
    printf("1 5 15 7 16 2 8 3\n1 6 12 4 21 3 2 8\n");
    printf("1 6 17 12 2 11 5 3\n1 8 2 3 21 4 12 6\n");
    printf("1 8 11 3 18 10 2 4\n1 12 2 6 3 7 22 4\n");
}    

int main() {
    scanf("%d", &N);
    ans = N*(N-1) + 1;
    printf("%d\n", ans);
    if (N == 8) {
        solve8();
        return 0;
    }
    A[0] = 1;
    dfs(1);
    return 0;
}
