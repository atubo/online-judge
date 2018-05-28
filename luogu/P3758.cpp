// https://www.luogu.org/problemnew/show/P3758
// [TJOI2017]可乐

#include <bits/stdc++.h>
using namespace std;

const int MOD = 2017;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (a * b) % MOD;
}

// square matrix fast power
class Matrix {
public:
    vector<vector<int>> _m;
    int _n;

public:
    Matrix(int n): _n(n) {
        _m.resize(n);
        for (int i = 0; i < n; i++) {
            _m[i].resize(n);
        }
    }

    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                for (int k = 0; k < _n; k++) {
                    //ret._m[i][j] += _m[i][k] * rhs._m[k][j];
                    ret._m[i][j] = add(ret._m[i][j],
                                       mul(_m[i][k], rhs._m[k][j]));
                }
            }
        }
        swap(ret);
        return *this;
    }

    void swap(Matrix &other) {
        _m.swap(other._m);
    }

    static Matrix power(const Matrix &x, int n) {
        if (n == 1) return x;
        Matrix y = power(x, n/2);
        y *= y;
        if (n & 1) y *= x;
        return y;
    }

    void print() const {
        for (int i = 0; i < _n; i++) {
            for (int x: _m[i]) {
                printf("%d ", x);
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

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    Matrix m(2*N);
    for (int i = 0; i < N; i++) {
        m._m[2*i][2*i] = m._m[2*i][2*i+1] = 1;
        m._m[2*i+1][2*i+1] = 1;
        for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            m._m[2*i+1][2*v+1] = 1;
        }
    }
    int T;
    scanf("%d", &T);
    Matrix mp = Matrix::power(m, T);
    int ans = 0;
    for (int i = 0; i < 2*N; i++) {
        ans = add(ans, mp._m[i][1]);
    }
    printf("%d\n", ans);
    return 0;
}
