// https://www.luogu.org/problem/show?pid=1286
// 两数之和

#include <bits/stdc++.h>
using namespace std;

int N, M;
int S[70], A[12];
bool used[70];

bool check(int idx, int p, vector<int>& added) {
    int x = S[idx] - A[0];
    if (x < A[p-1]) return false;
    for (int i = 0; i < p; i++) {
        int target = A[i] + x;
        int* it = lower_bound(S, S + M, target);
        int j = it - S;
        while (j < M&& S[j] == target && used[j]) j++;
        if (j == M|| S[j] != target) return false;
        used[j] = true;
        added.push_back(j);
    }

    A[p] = x;
    return true;
}

bool dfs(int p) {
    if (p == N) return true;
    for (int i = 0; i < M; i++) {
        if (!used[i]) {
            vector<int> added;
            if (check(i, p, added)) {
                if (dfs(p+1)) return true;
            }
            for (int j: added) {
                used[j] = false;
            }
        }
    }
    return false;
}

void solve() {
    bool found = false;
    for (int i = 2; i < M; i++) {
        if (((S[0] ^ S[1] ^ S[i]) & 1) == 0) {
            used[0] = used[1] = used[i] = true;
            A[0] = (S[0] + S[1] - S[i]) >> 1;
            A[1] = (S[0] + S[i] - S[1]) >> 1;
            A[2] = (S[1] + S[i] - S[0]) >> 1;
            if (dfs(3)) {
                found = true;
                break;
            }
            used[i] = false;
        }
    }

    if (found) {
        for (int i = 0; i < N; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
    } else {
        printf("Impossible\n");
    }
}

int main() {
    while (scanf("%d", &N) == 1) {
        M = N * (N-1) / 2;
        for (int i = 0; i < M; i++) {
            scanf("%d", &S[i]);
        }
        sort(S, S + M);
        memset(used, 0, sizeof(used));

        solve();
    }
    return 0;
}
