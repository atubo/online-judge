// https://www.luogu.com.cn/problem/P3808
// 【模板】AC自动机（简单版）

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
  static constexpr const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  static const int ALPHA_SIZE = strlen(ALPHABET);
 public:
  const int n_;
  int **to;
  //vector<set<int> > out;
  int *out;
  int sz = 1;
  int *link;  // blue link in the wiki
  int *next;  // green link in the wiki
  int *que;
  bool *vis;
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
    vis  = new bool[n_]{};
    out  = new int[n_]{};
  }

  ~AhoCorasick() {
    for (int i = 0; i < n_; i++) {
      delete[] to[i];
    }
    delete[] to;

    delete[] link;
    delete[] next;
    delete[] que;
    delete[] vis;
    delete[] out;
  }

  void add_str(const string &s) {
    int v = 0;
    for(int i = 0; i < (int)s.length(); i++) {
      int c = s[i] - ALPHABET[0];
      if(!to[v][c]) to[v][c] = sz++;
      v = to[v][c];
    }
    //out[v].insert(keywordIndex++);
    out[v]++;
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

  int64_t countTotalMatches(const string &t) {
    int64_t result = 0;
    int q = 0;
    for (int i = 0; i < (int)t.length(); i++) {
      int c = t[i] - ALPHABET[0];
      while (q != -1 && to[q][c] == 0) {
        q = link[q];
      }
      if (q != -1) {
        q = to[q][c];
        result += followDictSuffixLink(q);
      } else {
        q = 0;
      }
    }
    return result;
  }

 private:
  int64_t followDictSuffixLink(int q) const {
    int64_t res = 0;
    while (q != 0) {
      if (vis[q]) break;
      vis[q] = true;
      res += out[q];
      q = next[q];
    }
    return res;
  }
};

const int MAXL = 500010;

int main() {
  AhoCorasick ac(MAXL);
  int n;
  scanf("%d", &n);
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    ac.add_str(s);
  }
  ac.push_links();
  
  cin >> s;
  printf("%ld\n", ac.countTotalMatches(s));
  return 0;
}
