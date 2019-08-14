// https://www.luogu.org/problem/P3514
// [POI2011]LIZ-Lollipop

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int N, M;
int A[MAXN];
struct Data {
    int l, r;
} D[2*MAXN];

void process(int left, int right) {
    int tot = 0;
    for (int i = left; i <= right; i++) tot += A[i];
    D[tot] = {left, right};
    int n = tot, l = left, r = right;
    while (n > 2) {
        n -= 2;
        if (A[l] == 1 && A[r] == 1) {
            D[n] = {++l, --r};
        } else if (A[l] == 2) {
            D[n] = {++l, r};
        } else {
            D[n] = {l, --r};
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    string s;
    cin >> s;
    for (int i = 1; i <= N; i++) {
        A[i] = (s[i-1] == 'T' ? 2 : 1);
    }
    int id = INT_MAX;
    int l, r;
    for (int i = 1; i <= N; i++) {
        if (A[i] == 1) {
            int t = min(i-1, N-i);
            if (t < id) {
                id = t;
                if (i-1 < N-i) {
                    l = i+1;
                    r = N;
                } else {
                    l = 1;
                    r = i-1;
                }
            }
        }
    }

    if (id != INT_MAX) process(l, r);
    process(1, N);

    for (int i = 0; i < M; i++) {
        int k;
        scanf("%d", &k);
        if (D[k].l == 0) printf("NIE\n");
        else {
            printf("%d %d\n", D[k].l, D[k].r);
        }
    }

    return 0;
}
