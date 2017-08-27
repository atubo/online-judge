// https://www.luogu.org/problem/show?pid=1816
// 忠诚

#include <bits/stdc++.h>
using namespace std;

int M;

class SparseTableRMQ {
public:
    int N, MAXB;
    vector<int> A;
    vector<vector<int> > st;

public:
    SparseTableRMQ() {
        scanf("%d%d", &N, &M);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
            MAXB++;
            x = x * 2;
        }

        st.resize(N);
        for (int i = 0; i < N; i++) {
            st[i].resize(MAXB, INT_MAX);
            st[i][0] = A[i];
        }

        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int rmq(int u, int v) {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return min(st[u][j], st[v+1-(1<<j)][j]);
    }
};

int main() {
    SparseTableRMQ st;
    st.preCompute();

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d ", st.rmq(u-1, v-1));
    }
    printf("\n");
    return 0;
}
