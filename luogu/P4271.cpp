// https://www.luogu.com.cn/problem/P4271
// [USACO18FEB]New Barns P

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
            size_vc_[x] += size[c_[x][1]] - size[t];
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
        size_vc_[y] += size[x];
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

    int queryTot(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return tot_[y];
    }

    void update(int u, int v, int d) {
        makeRoot(u);
        access(v);
        splay(v);
        updateAdd(v, d);
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
        printf("tot: ");
        for (int i = 1; i <= N_; i++) {
            printf("%d ", tot_[i]);
        }
        printf("\n");
        printf("d: ");
        for (int i = 1; i <= N_; i++) {
            printf("%d ", delta_[i]);
        }
        printf("\n");
    }

public:
    int *val;
    int *size;  // size of subtree in the original tree
    int *sz_;    // size of subtree in the splay tree
private:
    const int N_;
    int *fa_, *mx_, *tot_, *delta_;
    int *size_vc_;   // size of virtual children
    int **c_;
    int *q_;
    bool *rev_;

    void alloc() {
        fa_ = new int[N_+1]{};
        val = new int[N_+1]{};
        mx_ = new int[N_+1]{};
        tot_ = new int[N_+1]{};
        delta_ = new int[N_+1]{};
        sz_ = new int[N_+1]{};
        size = new int[N_+1]{};
        size_vc_ = new int[N_+1]{};
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
        delete[] tot_;
        delete[] delta_;
        delete[] sz_;
        delete[] size;
        delete[] size_vc_;
        for (int i = 0; i <= N_; i++) {
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

        updateAdd(l, delta_[x]);
        updateAdd(r, delta_[x]);
        delta_[x] = 0;
    }

    void pushUp(int x) {
        int l = c_[x][0], r = c_[x][1];
        mx_[x] = val[x];
        mx_[x] = max(mx_[x], mx_[l]);
        mx_[x] = max(mx_[x], mx_[r]);
        sz_[x] = 1 + sz_[l] + sz_[r];
        tot_[x] = val[x] + tot_[l] + tot_[r];
        size[x] = size[l] + size[r] + size_vc_[x] + 1;
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

    void updateAdd(int x, int d) {
        if (!x) return;

        tot_[x] += d * sz_[x];
        val[x] += d;
        delta_[x] += d;
    }
};

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
        ends[k] = {k, k};
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    vector<pair<int, int>> ends;

    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);
        ends.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

const int MAXQ = 100010;
int Q;
int D[MAXQ];

int main() {
  scanf("%d", &Q);
  char buf[3];
  int curr = 0;
  LinkCutTree lct(Q);
  UnionFind uf(Q+1);
  while (Q--) {
    int a;
    scanf("%s%d", buf, &a);
    if (buf[0] == 'B') {
      curr++;
      if (a == -1) continue;
      int p = uf.find(a);
      lct.link(curr, a);
      lct.split(uf.ends[p].first, curr);
      int mx1 = lct.sz_[curr] - 1;
      lct.split(uf.ends[p].second, curr);
      int mx2 = lct.sz_[curr] - 1;
      int p2 = uf.join(p, curr);
      uf.ends[p2] = uf.ends[p];
      D[p2] = D[p];
      p = p2;
      if (mx1 > D[p]) {
        D[p] = mx1;
        uf.ends[p] = {curr, uf.ends[p].first};
      }
      if (mx2 > D[p]) {
        D[p] = mx2;
        uf.ends[p] = {curr, uf.ends[p].second};
      }
    } else {
      int p = uf.find(a);
      lct.split(uf.ends[p].first, a);
      int mx1 = lct.sz_[a] - 1;
      lct.split(uf.ends[p].second, a);
      int mx2 = lct.sz_[a] - 1;
      printf("%d\n", max(mx1, mx2));
    }
  }

  return 0;
}
