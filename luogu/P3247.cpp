// https://www.luogu.com.cn/problem/P3247
// [HNOI2016]最小公倍数

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
 struct Op {
   Op(): op(-1), x(0), y(0) {}
   Op(int _op, int _x, int _y): op(_op), x(_x), y(_y) {}
   int op, x, y;
 };

 const int n_;
 vector<int> rank_;
 vector<int> parent_;
 vector<Op> ops_;

 void makeSet(int k) {
   assert(0 <= k && k < n_);

   parent_[k] = k;
   rank_[k] = 0;
   va_[k] = vb_[k] = -1;
 }

 void link(int u, int v, int a, int b, int type) {
   if (u != v) {
     if (rank_[u] == rank_[v]) {
       if (type) push(1, u, rank_[u]);
       rank_[u]++;
     }
     if (rank_[u] < rank_[v]) swap(u, v);
     if (type) push(0, v, v);
     parent_[v] = u;
     if (va_[u] < va_[v] && va_[v] > a) {
       if (type) push(2, u, va_[u]);
       va_[u] = va_[v];
     }
     if (vb_[u] < vb_[v] && vb_[v] > b) {
       if (type) push(3, u, vb_[u]);
       vb_[u] = vb_[v];
     }
   }
   if (va_[u] < a) {
     if (type) push(2, u, va_[u]);
     va_[u] = a;
   }
   if (vb_[u] < b) {
     if (type) push(3, u, vb_[u]);
     vb_[u] = b;
   }
 }

 void push(int op, int x, int y) {
   ops_.emplace_back(op, x, y);
 }

public:
 vector<int> va_;
 vector<int> vb_;

 UnionFind(int n): n_(n) {
   rank_.resize(n_);
   parent_.resize(n_);
   va_.resize(n_);
   vb_.resize(n_);
   ops_.reserve(n_);

   reset();
 }

 void reset() {
   ops_.clear();
   for (int i = 0; i < n_; i++) {
     makeSet(i);
   }
 }

 int find(int k) const {
   if (parent_[k] == k) return k;
   return find(parent_[k]);
 }

 void join(int u, int v, int a, int b, int type) {
   link(find(u), find(v), a, b, type);
 }

 void backtrace() {
   for (int i = ops_.size()-1; i >= 0; i--) {
     switch (ops_[i].op) {
       case 0:
         parent_[ops_[i].x] = ops_[i].y;
         break;
       case 1:
         rank_[ops_[i].x] = ops_[i].y;
         break;
       case 2:
         va_[ops_[i].x] = ops_[i].y;
         break;
       case 3:
         vb_[ops_[i].x] = ops_[i].y;
         break;
       default:
         assert(0);
         break;
     }
   }
   ops_.clear();
 }
};

const int MAXN = 50010, MAXM = 100010;
int N, M, Q;
int A[MAXM], B[MAXN], ans[MAXN];

struct Edge {
  int x, y, a, b;
} E[MAXM], I[MAXN];

bool cmpa(const Edge& a, const Edge& b) {
  return a.a < b.a;
}

bool cmpe(int x, int y) {
  return E[x].b < E[y].b;
}

bool cmpq(int x, int y) {
  return I[x].b < I[y].b;
}

int main() {
  scanf("%d%d", &N, &M);
  int lim = 0;
  while (lim*lim < M) lim++;
  for (int i = 0; i < M; i++) {
    int x, y, a, b;
    scanf("%d%d%d%d", &x, &y, &a, &b);
    E[i] = {x-1, y-1, a, b};
    A[i] = i;
  }
  sort(E, E+M, cmpa);
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    int x, y, a, b;
    scanf("%d%d%d%d", &x, &y, &a, &b);
    I[i] = {x-1, y-1, a, b};
  }
  UnionFind uf(N);
  for (int i = 0; i < M; i+=lim) {
    int cnt = 0;
    for (int j = 0; j < Q; j++) {
      if (I[j].a >= E[i].a && (i+lim >= M || I[j].a < E[i+lim].a)) {
        B[cnt++] = j;
      }
    }
    if (!cnt) continue;
    sort(A, A+i, cmpe);
    sort(B, B+cnt, cmpq);
    uf.reset();
    for (int j=0, k=0; j < cnt; j++) {
      while (k < i && E[A[k]].b <= I[B[j]].b) {
        uf.join(E[A[k]].x, E[A[k]].y, E[A[k]].a, E[A[k]].b, 0);
        k++;
      }
      for (int o = min(i+lim-1, M-1); o >= i; o--) {
        if (E[o].a <= I[B[j]].a && E[o].b <= I[B[j]].b) {
          uf.join(E[o].x, E[o].y, E[o].a, E[o].b, 1);
        }
      }
      int x = uf.find(I[B[j]].x);
      int y = uf.find(I[B[j]].y);
      if (x == y && uf.va_[x] == I[B[j]].a && uf.vb_[x] == I[B[j]].b) {
        ans[B[j]] = 1;
      }
      uf.backtrace();
    }
  }

  for (int i = 0; i < Q; i++) {
    printf(ans[i] ? "Yes\n" : "No\n");
  }

  return 0;
}
