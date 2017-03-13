// https://www.luogu.org/problem/show?pid=3095
// [USACO13DEC]贝西洗牌The Bessie Shuffle

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

void print(const vector<int>& A) {
    for (int x: A) {
        printf("%d ", x);
    }
    printf("\n");
}

void power(vector<int>& R, const vector<int>& R0, vector<int>& tmp, int s, int n, int L) {
    if (n == 1) return;
    if (n == 0) {
        for (int i = 0, p = s; i < L; i++) {
            R[p] = p;
            p = R0[p];
        }
        return;
    }
    power(R, R0, tmp, s, n/2, L);
    for (int i = 0, p = s; i < L; i++) {
        tmp[p] = R[R[p]];
        p = R0[p];
    }
    if (n & 1) {
        for (int i = 0, p = s; i < L; i++) {
            tmp[p] = R0[tmp[p]];
            p = R0[p];
        }
    }

    for (int i = 0, p = s; i < L; i++) {
        R[p] = tmp[p];
        p = R0[p];
    }
}

int main() {
    int N, M, T;
    scanf("%d %d %d", &N, &M, &T);
    vector<int> P(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &P[i]);
        P[i]--;
    }

    vector<int> Q(M);
    for (int i = 0; i < M; i++) {
        Q[P[i]] = i;
    }

    vector<PII> head;
    vector<int> R(M, -2);
    {
        int q = M-1;
        int len = 0;
        do {
            q = R[q] = P[q] - 1;
            len++;
        } while (q != -1);
        head.push_back(make_pair(M-1, len));
    }

    for (int i = 0; i < M-1; i++) {
        int q = i;
        if (R[q] == -2) {
            int len = 0;
            do {
                q = R[q] = P[q] - 1;
                len++;
            } while (R[q] == -2);
            head.push_back(make_pair(i, len));
        }
    }

#if 0
    print(R);
    for (auto p: head) {
        printf("%d %d\n", p.first, p.second);
    }
#endif

    const int L = head[0].second;
    vector<int> w(L + N - M);
    for (int i = L - 1, q = M - 1; i >= 0; i--) {
        w[i] = q + 1;
        q = R[q];
    }
    for (int i = L; i < L + N - M; i++) {
        w[i] = M + 1 + (i - L);
    }

    //print(w);

    vector<int> ret(N);
    for (int i = 0; i < N - M; i++) {
        ret[i] = w[i];
    }

    vector<int> u(M);
    vector<int> tmp(M);
    for (int i = L - 1, q = M - 1; i >= 0; i--) {
        u[q] = w[i + N - M];
        q = R[q];
    }

    vector<int> R0 = R;
    for (int i = 1; i < (int)head.size(); i++) {
        power(R, R0, tmp, head[i].first, (N-M) % head[i].second, head[i].second);
        for (int j = 0, p = head[i].first; j < head[i].second; j++) {
            u[R[p]] = p + 1;
            p = R0[p];
        }
    }
    //print(u);

    for (int i = 0; i < M; i++) {
        tmp[P[i]] = u[i];
    }
    //print(tmp);

    for (int i = N - M; i < N; i++) {
        ret[i] = tmp[i - N + M];
    }

    //print(ret);

    for (int i = 0; i < T; i++) {
        int q;
        scanf("%d", &q);
        printf("%d\n", ret[N-q]);
    }

    return 0;
}
