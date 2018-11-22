// https://www.luogu.org/problemnew/show/P1215
// [USACO1.4]母亲的牛奶 Mother's Milk

#include <bits/stdc++.h>
using namespace std;

const int MASK = 0x1F;
int A, B, C;
bool vis[1<<15];
bool feasible[22];

int encode(int a, int b, int c) {
    return (a << 10) | (b << 5) | c;
}

void decode(int code, int &a, int &b, int &c) {
    c = (code) & MASK;
    b = (code >> 5) & MASK;
    a = (code >> 10) & MASK;
}

void pour(int a, int b, int tc, int &a2, int &b2) {
    if (a > (tc - b)) {
        a2 = a - (tc - b);
        b2 = tc;
    } else {
        a2 = 0;
        b2 = b + a;
    }
}

void dfs(int code) {
    vis[code] = true;
    int a, b, c;
    decode(code, a, b, c);
    if (a == 0) feasible[c] = true;

    if (a > 0) {
        int a2, b2, c2;
        pour(a, b, B, a2, b2);
        int code2 = encode(a2, b2, c);
        if (!vis[code2]) dfs(code2);
        pour(a, c, C, a2, c2);
        code2 = encode(a2, b, c2);
        if (!vis[code2]) dfs(code2);
    }
    if (b > 0) {
        int a2, b2, c2;
        pour(b, a, A, b2, a2);
        int code2 = encode(a2, b2, c);
        if (!vis[code2]) dfs(code2);
        pour(b, c, C, b2, c2);
        code2 = encode(a, b2, c2);
        if (!vis[code2]) dfs(code2);
    }
    if (c > 0) {
        int a2, b2, c2;
        pour(c, a, A, c2, a2);
        int code2 = encode(a2, b, c2);
        if (!vis[code2]) dfs(code2);
        pour(c, b, B, c2, b2);
        code2 = encode(a, b2, c2);
        if (!vis[code2]) dfs(code2);
    }
}

int main() {
    scanf("%d%d%d", &A, &B, &C);
    dfs(encode(0, 0, C));
    for (int i = 0; i <= C; i++) {
        if (feasible[i]) printf("%d ", i);
    }
    return 0;
}
