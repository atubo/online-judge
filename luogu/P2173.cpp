// https://www.luogu.org/problemnew/show/P2173
// [ZJOI2012]网络

#include <bits/stdc++.h>
using namespace std;

class LinkCutTree {
    // tree nodes are 1-indexed

public:
    LinkCutTree(int N): N_(N) {
        alloc();
    }

    ~LinkCutTree() {
        dealloc();
    }

    void access(int x) {
        for (int t = 0; x; t=x, x=fa_[x]) {
            splay(x);
            c_[x][1] = t;
            pushUp(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        rev_[x] ^= 1;
    }

    void link(int x, int y) {
        makeRoot(x);
        makeRoot(y);
        fa_[x] = y;
        splay(x);
        pushUp(y);
    }

    // split out the path from x to y
    void split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
    }

    void cut(int x, int y) {
        split(x, y);
        c_[y][0] = fa_[x] = 0;
        pushUp(y);
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c_[y][0]) y = c_[y][0];
        return y;
    }

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return mx_[y];
    }

    void update(int u, int d) {
        makeRoot(u);
        access(u);
        val[u] += d;
    }

    void print() {
        printf("father: ");
        for (int i = 1; i <= N_; i++) {
            printf("%d ", fa_[i]);
        }
        printf("\n");
        printf("child: ");
        for (int i = 1; i <= N_; i++) {
            printf("(%d %d) ", c_[i][0], c_[i][1]);
        }
        printf("\n");
        printf("rev: ");
        for (int i = 1; i <= N_; i++) {
            printf("%d ", int(rev_[i]));
        }
        printf("\n");

        printf("val: ");
        for (int i = 1; i <= N_; i++) {
            printf("%d ", val[i]);
        }
        printf("\n");
    }

public:
    int *val;
private:
    const int N_;
    int *fa_, *mx_;
    int *sz_;    // size of subtree in the splay tree
    int **c_;
    int *q_;
    bool *rev_;

    void alloc() {
        fa_ = new int[N_+1]{};
        val = new int[N_+1]{};
        mx_ = new int[N_+1]{};
        sz_ = new int[N_+1]{};
        c_ = new int*[N_+1]{};
        for (int i = 0; i <= N_; i++) {
            c_[i] = new int[2]{};
        }
        q_ = new int[N_+1]{};
        rev_ = new bool[N_+1]{};
    }

    void dealloc() {
        delete[] fa_;
        delete[] val;
        delete[] mx_;
        delete[] sz_;
        for (int i = 1; i <= N_; i++) {
            delete[] c_[i];
        }
        delete[] c_;
        delete[] q_;
        delete[] rev_;
    }

    bool isSplayRoot(int x) {
        return c_[fa_[x]][1] != x && c_[fa_[x]][0] != x;
    }

    void pushDown(int x) {
        int l = c_[x][0], r = c_[x][1];
        if (rev_[x]) {
            rev_[x] ^= 1; rev_[l] ^= 1; rev_[r] ^= 1;
            swap(c_[x][1], c_[x][0]);
        }
    }

    void pushUp(int x) {
        int l = c_[x][0], r = c_[x][1];
        mx_[x] = val[x];
        mx_[x] = max(mx_[x], mx_[l]);
        mx_[x] = max(mx_[x], mx_[r]);
        sz_[x] = 1 + sz_[l] + sz_[r];
    }

    void rotate(int x) {
        int y = fa_[x], z = fa_[y], l, r;
        l = (c_[y][1] == x); r = l^1;
        if (!isSplayRoot(y)) c_[z][c_[z][1]==y] = x;
        fa_[c_[x][r]] = y; fa_[y] = x; fa_[x] = z;
        c_[y][l] = c_[x][r]; c_[x][r] = y;
        pushUp(y); pushUp(x);
    }

    void splay(int x) {
        int top = 0;
        q_[++top] = x;
        for (int i = x; !isSplayRoot(i); i = fa_[i]) {
            q_[++top] = fa_[i];
        }
        while (top) pushDown(q_[top--]);
        while (!isSplayRoot(x)) {
            int y = fa_[x], z = fa_[y];
            if (!isSplayRoot(y)) {
                if ((c_[y][0] == x) ^ (c_[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
};

const int MAXN = 10010;
const int MAXM = 100010;
int N, M, C, K;
int weight[MAXN];
int id[MAXM], color[MAXM];
int deg[11][MAXN];

int encode(int u, int v) {
    if (u > v) swap(u, v);
    return u * (N+1) + v;
}

void decode(int c, int &u, int &v) {
    v = c % (N+1);
    u = c / (N+1);
}

struct Edge {
    int id, u, v, c;
    bool operator < (const Edge &other) const {
        return id < other.id;
    }
};

void updateNode(vector<LinkCutTree*> &lcf) {
    int x, y;
    scanf("%d%d", &x, &y);
    int d = y - weight[x];
    for (int i = 0; i < C; i++) {
        lcf[i]->update(x, d);
    }
    weight[x] = y;
}

void updateEdge(vector<LinkCutTree*> &lcf) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    int code = encode(u, v);
    int eidx = lower_bound(id, id+M, code) - id;
    if (id[eidx] != code) {
        printf("No such edge.\n");
        return;
    }
    int oc = color[eidx];
    if (oc == c) {
        printf("Success.\n");
        return;
    }
    if (deg[c][u] == 2 || deg[c][v] == 2) {
        printf("Error 1.\n");
        return;
    }
    if (lcf[c]->find(u) == lcf[c]->find(v)) {
        printf("Error 2.\n");
        return;
    }
    lcf[c]->link(u, v);
    deg[c][u]++;
    deg[c][v]++;
    color[eidx] = c;
    lcf[oc]->cut(u, v);
    deg[oc][u]--;
    deg[oc][v]--;
    printf("Success.\n");
}

void query(vector<LinkCutTree*> &lcf) {
    int c, u, v;
    scanf("%d%d%d", &c, &u, &v);
    int ans = -1;
    if (lcf[c]->find(u) == lcf[c]->find(v)) {
        ans = lcf[c]->query(u, v);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d%d%d", &N, &M, &C, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &weight[i]);
    }
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        edges[i] = {encode(u, v), u, v, c};
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < M; i++) {
        id[i] = edges[i].id;
        color[i] = edges[i].c;
    }
    vector<LinkCutTree*> lcf(C);
    for (int i = 0; i < C; i++) {
        lcf[i] = new LinkCutTree(N);
        for (int j = 1; j <= N; j++) {
            lcf[i]->val[j] = weight[j];
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        decode(id[i], u, v);
        int c = color[i];
        lcf[c]->link(u, v);
        deg[c][u]++;
        deg[c][v]++;
    }

    for (int i = 0; i < K; i++) {
        int k;
        scanf("%d", &k);
        switch (k) {
            case 0:
                updateNode(lcf);
                break;
            case 1:
                updateEdge(lcf);
                break;
            case 2:
                query(lcf);
                break;
        }
    }

    return 0;
}
