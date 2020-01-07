// https://www.luogu.com.cn/problem/P5357
// 【模板】AC自动机（二次加强版）

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
  static constexpr const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  static const int ALPHA_SIZE = strlen(ALPHABET);
 public:
  const int n_;
  int **to;
  int *out;
  int sz = 1;
  int *link;  // blue link in the wiki
  int *next;  // green link in the wiki
  int *que;
  int *node;
  int *cnt;
  int *deg;
  int keywordIndex;

  // n is total length, total number of nodes is at most n+1
  AhoCorasick(int n): n_(n+1), keywordIndex(0) {
    to = new int*[n_]{};
    for (int i = 0; i < n_; i++) {
      to[i] = new int[ALPHA_SIZE]{};
    }

    link = new int[n_]{};
    next = new int[n_]{};
    que  = new int[n_]{};
    out  = new int[n_]{};
    node = new int[n_]{};
    cnt  = new int[n_]{};
    deg  = new int[n_]{};
  }

  ~AhoCorasick() {
    for (int i = 0; i < n_; i++) {
      delete[] to[i];
    }
    delete[] to;

    delete[] link;
    delete[] next;
    delete[] que;
    delete[] out;
    delete[] node;
    delete[] cnt;
    delete[] deg;
  }

  void add_str(const string &s) {
    int v = 0;
    for(int i = 0; i < (int)s.length(); i++) {
      int c = s[i] - ALPHABET[0];
      if(!to[v][c]) to[v][c] = sz++;
      v = to[v][c];
    }
    out[v] = 1;
    node[keywordIndex++] = v;
  }

  void push_links() {
    link[0] = -1;
    int st = 0, fi = 1;
    que[0] = 0;
    while (st < fi) {
      int v = que[st++];
      for (int c = 0; c < ALPHA_SIZE; c++) {
        int u = to[v][c];
        if (u == 0) continue;
        int j = link[v];
        while(j != -1 && !to[j][c]) j = link[j];
        if(j != -1) link[u] = to[j][c];
        if (out[link[u]] == 0) {
          next[u] = next[link[u]];
        } else {
          next[u] = link[u];
        }
        que[fi++] = u;
      }
    }
  }

  void countTotalMatches(const string &t) {
    int q = 0;
    for (int i = 0; i < (int)t.length(); i++) {
      int c = t[i] - ALPHABET[0];
      while (q != -1 && to[q][c] == 0) {
        q = link[q];
      }
      if (q != -1) {
        q = to[q][c];
        cnt[q]++;
      } else {
        q = 0;
      }
    }
  }

  void followDictSuffixLink() const {
    for (int i = n_-1; i >= 1; i--) {
      cnt[next[i]] += cnt[i];
    }
  }

  void topo() {
    for (int i = 1; i < sz; i++) {
      deg[next[i]]++;
    }
    int st = 0, fi = 1;
    for (int i = 1; i < sz; i++) {
      if (deg[i] == 0) que[fi++] = i;
    }
    while (st < fi) {
      int u = que[st++];
      int v = next[u];
      if (v == 0) continue;
      cnt[v] += cnt[u];
      deg[v]--;
      if (deg[v] == 0) {
        que[fi++] = v;
      }
    }
  }
};

const int MAXL = 200010;

int main() {
  string s;
  int n;
  scanf("%d", &n);
  AhoCorasick ac(MAXL);
  for (int i = 0; i < n; i++) {
    cin >> s;
    ac.add_str(s);
  }
  ac.push_links();
  cin >> s;
  ac.countTotalMatches(s);
  ac.topo();
  for (int i = 0; i < n; i++) {
    printf("%d\n", ac.cnt[ac.node[i]]);
  }
  return 0;
}
