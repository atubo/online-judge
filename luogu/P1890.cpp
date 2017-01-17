// https://www.luogu.org/problem/show?pid=1890
// P1890 gcd区间

#include <cstdio>
#include <vector>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    typedef vector<vector<int> > Table;
    int N, M;
    scanf("%d %d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    Table table(N);
    for (int i = 0; i < N; i++) {
        table[i].resize(N-i+1);
    }

    for (int i = 0; i < N; i++) {
        table[i][1] = A[i];
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i < N+1-len; i++) {
            table[i][len] = gcd(table[i][len-1], A[i+len-1]);
        }
    }

    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        printf("%d\n", table[l][r-l]);
    }
    return 0;
}
