// https://www.luogu.org/problemnew/show/P2151
// [SDOI2009]HH去散步

#include <bits/stdc++.h>
using namespace std;

const int MOD = 45989;
// square matrix fast power
class Matrix {
public:
    int **_m;
    int _n;

public:
    Matrix(int n): _n(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        _n = other._n;
        alloc();
        for (int i = 0; i < _n; i++) {
            memcpy(_m[i], other._m[i], _n * sizeof(int));
        }
    }


    ~Matrix() {
        for (int i = 0; i < _n; i++) {
            delete[] _m[i];
        }
        delete _m;
    }

    void alloc() {
        _m = new int*[_n]{};
        for (int i = 0; i < _n; i++) {
            _m[i] = new int[_n]{};
        }
    }


#if 0
    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                for (int k = 0; k < _n; k++) {
                    ret._m[i][j] += (_m[i][k] * rhs._m[k][j]) % MOD;
                    ret._m[i][j] %= MOD;
                }
            }
        }
        swap(ret);
        return *this;
    }
#endif

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < _n; i++) {
            memset(tmp._m[i], 0, _n * sizeof(int));
            for (int k = 0; k < _n; k++) {
                if (!_m[i][k]) continue;
                for (int j = 0; j < _n; j++) {
                    tmp._m[i][j] += _m[i][k] * rhs._m[k][j];
                    tmp._m[i][j] %= MOD;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(_m, other._m);
    }

    static Matrix power(Matrix x, int n) {
        Matrix ret(x._n), tmp(x._n);
        for (int i = 0; i < x._n; i++) ret._m[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, tmp);
            x.mul(x, tmp);
            n >>= 1;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                printf("%d ", _m[i][j]);
            }
            printf("\n");
        }
    }
};

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

int N, M, T, A, B;

int main() {
    scanf("%d%d%d%d%d", &N, &M, &T, &A, &B);
    Graph g(N+1, 2*M+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    g.addEdge(N, A);
    Matrix mat(2*M+1);
    for (int u = 0; u < N; u++) {
        for (int e1p = g.head[u]; ~e1p; e1p = g.E[e1p].next) {
            for (int e2 = g.head[u]; ~e2; e2 = g.E[e2].next) {
                if (e1p == e2) continue;
                mat._m[e2][e1p^1]++;
            }
        }
    }
    for (int e = g.head[A]; ~e; e = g.E[e].next) {
        mat._m[e][2*M]++;
    }

    Matrix mp = Matrix::power(mat, T);
    int ans = 0;
    for (int e = g.head[B]; ~e; e = g.E[e].next) {
        (ans += mp._m[e^1][2*M]) %= MOD;
    }
    printf("%d\n", ans);
    return 0;
}
