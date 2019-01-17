// https://www.luogu.org/problemnew/show/P2579
// [ZJOI2005]沼泽鳄鱼

#include <bits/stdc++.h>
using namespace std;

// square matrix fast power
class Matrix {
public:
    int **m_;
    int n_;

public:
    Matrix(int n): n_(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        n_ = other.n_;
        alloc();
        for (int i = 0; i < n_; i++) {
            memcpy(m_[i], other.m_[i], n_ * sizeof(int));
        }
    }


    ~Matrix() {
        for (int i = 0; i < n_; i++) {
            delete[] m_[i];
        }
        delete[] m_;
    }

    static Matrix power(Matrix x, int64_t n) {
        Matrix ret(x.n_), tmp(x.n_);
        for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, tmp);
            x.mul(x, tmp);
            n >>= 1;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                printf("%d ", m_[i][j]);
            }
            printf("\n");
        }
    }

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < n_; i++) {
            memset(tmp.m_[i], 0, n_ * sizeof(int));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    (tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j]) %= 10000;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
private:
    void alloc() {
        m_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            m_[i] = new int[n_]{};
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

const int MAXN = 52;
int N, M, Start, End, K;
bool danger[MAXN][12];

void calcDanger() {
    int nfish;
    scanf("%d", &nfish);
    for (int i = 0; i < nfish; i++) {
        int t, p0, p1, p2, p3;
        scanf("%d", &t);
        if (t == 2) {
            scanf("%d%d", &p0, &p1);
            for (int j = 0; j < 12; j++) {
                if (j % t == 0) danger[p0][j] = true;
                else danger[p1][j] = true;
            }
        } else if (t == 3) {
            scanf("%d%d%d", &p0, &p1, &p2);
            for (int j = 0; j < 12; j++) {
                if (j % t == 0) danger[p0][j] = true;
                else if (j % t == 1) danger[p1][j] = true;
                else danger[p2][j] = true;
            }
        } else {
            scanf("%d%d%d%d", &p0, &p1, &p2, &p3);
            for (int j = 0; j < 12; j++) {
                if (j % t == 0) danger[p0][j] = true;
                else if (j % t == 1) danger[p1][j] = true;
                else if (j % t == 2) danger[p2][j] = true;
                else danger[p3][j] = true;
            }
        }
    }
}

Matrix build(const Graph &g, int t) {
    Matrix ret(N);
    for (int u = 0; u < N; u++) {
        if (danger[u][t]) continue;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (danger[v][(t+1)%12]) continue;
            ret.m_[v][u]++;
        }
    }
    return ret;
}

int solve(const Graph &g) {
    Matrix ret(N), tmp(N);
    for (int i = 0; i < N; i++) ret.m_[i][i] = 1;
    for (int i = K%12 - 1; i >= 0; i--) {
        ret.mul(build(g, i), tmp);
    }
    int n = K / 12;
    if (n > 0) {
        Matrix m(N);
        for (int i = 0; i < N; i++) m.m_[i][i] = 1;
        for (int i = 11; i >= 0; i--) {
            m.mul(build(g, i), tmp);
        }
        ret.mul(Matrix::power(m, n), tmp);
    }
    return ret.m_[End][Start];
}

int main() {
    scanf("%d%d%d%d%d", &N, &M, &Start, &End, &K);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g.addEdge(x, y);
        g.addEdge(y, x);
    }
    calcDanger();

    int ans = solve(g);
    printf("%d\n", ans);
    return 0;
}
