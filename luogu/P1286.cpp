// https://www.luogu.org/problem/show?pid=1286
// 两数之和

#include <bits/stdc++.h>
using namespace std;

int N;
int S[70], A[12];

bool verify() {
    vector<int> actual;
    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            actual.push_back(A[i] + A[j]);
        }
    }
    sort(actual.begin(), actual.end());
    
    for (int i = 0; i < N*(N-1)/2; i++) {
        if (S[i] != actual[i]) return false;
    }
    return true;
}

int findMissing(int p, int q, const vector<int>& t) {
    assert((int)t.size() == q - p - 1);
    bool found = false;
    int ret = -1;
    for (int i = p, j = 0; i < q; i++, j++) {
        if (j == q-p-1 || S[i] != t[j]) {
            if (!found) {
                found = true;
                ret = S[i];
                j--;
            } else {
                return -1;
            }
        }
    }
    return ret;
}

bool guess(int a0) {
    int p = 0;
    A[0] = a0;
    for (int k = 1; k < N; k++) {
        int q = p + (k-1)/2 + 1;
        vector<int> tmp;
        for (int r = (k-1)/2; r >= 1; r--) {
            tmp.push_back(A[r] + A[k-r]);
        }
        sort(tmp.begin(), tmp.end());
        int x = findMissing(p, q, tmp);
        if (x == -1) return false;
        A[k] = x - A[0];
        p = q;
    }
    return verify();
}

void solve() {
    bool found = false;
    for (int a = 0; a <= S[0]/2; a++) {
        if (guess(a)) {
            found = true;
            break;
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
        for (int i = 0; i < N*(N-1)/2; i++) {
            scanf("%d", &S[i]);
        }
        sort(S, S + N*(N-1)/2);

        solve();
    }
    return 0;
}
