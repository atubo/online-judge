// https://www.luogu.org/problemnew/show/P1092
// 虫食算

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 26;
int N;
int A[MAXN], B[MAXN], C[MAXN];
int curr[MAXN];
bool taken[MAXN];

void read(int *x) {
    string s;
    cin >> s;
    for (int i = 0; i < N; i++) {
        x[i] = s[N-1-i] - 'A';
    }
}

inline void take(int letter, int x) {
    curr[letter] = x;
    taken[x] = true;
}

inline void release(int letter, int x) {
    curr[letter] = -1;
    taken[x] = false;
}

bool dfs(int pos, int carry);

bool search(int pos, int carry, int letter) {
    for (int x = N-1; x >= 0; x--) {
        if (!taken[x]) {
            take(letter, x);
            if (dfs(pos, carry)) return true;
            release(letter, x);
        }
    }
    return false;
}

inline bool prune(int pos) {
    for (int i = pos; i < N; i++) {
        int a = A[i], b = B[i], c = C[i];
        if (curr[a] >= 0 && curr[b] >= 0 && curr[c] >= 0 &&
            (curr[a] + curr[b]) % N != curr[c] &&
            (curr[a] + curr[b] + 1) % N != curr[c]) {
            return true;
        }
    }
    return false;
}

int solvec(int a, int b, int carry, int &nextcarry) {
    nextcarry = 0;
    int c = a + b + carry;
    if (c >= N) {
        c -= N;
        nextcarry = 1;
    }
    if (taken[c]) return -1;
    return c;
}

bool dfs(int pos, int carry) {
    if (pos == N) {
        if (carry == 0) {
            for (int i = 0; i < N; i++) {
                printf("%d ", curr[i]);
            }
            return true;
        } else {
            return false;
        }
    }

    if (prune(pos)) return false;

    int a = A[pos], b = B[pos], c = C[pos];
    if (curr[a] == -1) {
        return search(pos, carry, a);
    } else if (curr[b] == -1) {
        return search(pos, carry, b);
    } else if (curr[c] == -1) {
        int nextcarry;
        int xc = solvec(curr[a], curr[b], carry, nextcarry);
        if (xc < 0) return false;
        take(c, xc);
        if (dfs(pos+1, nextcarry)) return true;
        release(c, xc);
        return false;
    } else {
        int sumab = curr[a] + curr[b] + carry;
        if (sumab == curr[c]) return dfs(pos+1, 0);
        if (sumab == curr[c]+N) return dfs(pos+1, 1);
        return false;
    }
}


int main() {
    memset(curr, -1, sizeof(curr));
    cin >> N;
    read(A); read(B); read(C);
    dfs(0, 0);
    return 0;
}
