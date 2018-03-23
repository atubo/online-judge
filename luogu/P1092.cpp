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

void take(int letter, int x) {
    curr[letter] = x;
    taken[x] = true;
}

void release(int letter, int x) {
    curr[letter] = -1;
    taken[x] = false;
}

bool dfs(int pos, int carry);

bool search(int pos, int carry, int letter) {
    for (int i = 0; i < N; i++) {
        if (!taken[i]) {
            take(letter, i);
            if (dfs(pos, carry)) return true;
            release(letter, i);
        }
    }
    return false;
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

    int a = A[pos], b = B[pos], c = C[pos];
    if (curr[a] == -1) {
        return search(pos, carry, a);
    } else if (curr[b] == -1) {
        return search(pos, carry, b);
    } else if (curr[c] == -1) {
        int x = curr[a] + curr[b] + carry;
        if (x >= N) {
            x -= N;
            if (!taken[x]) {
                take(c, x);
                if (dfs(pos+1, 1)) return true;
                release(c, x);
            } else {
                return false;
            }
        } else {
            if (!taken[x]) {
                take(c, x);
                if (dfs(pos+1, 0)) return true;
                release(c, x);
            } else {
                return false;
            }
        }
    } else {
        int sumab = curr[a] + curr[b] + carry;
        if (sumab == curr[c]) return dfs(pos+1, 0);
        if (sumab == curr[c]+N) return dfs(pos+1, 1);
        return false;
    }
    return false;
}


int main() {
    memset(curr, -1, sizeof(curr));
    cin >> N;
    read(A); read(B); read(C);
    dfs(0, 0);
    return 0;
}
