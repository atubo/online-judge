// https://www.luogu.com.cn/problem/P3796
// 【模板】AC自动机（加强版）

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
  static constexpr const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  static const int ALPHA_SIZE = strlen(ALPHABET);
 public:
  const int n_;
  int **to;
  vector<set<int> > out;
  int sz = 1;
  int *link;  // blue link in the wiki
  int *next;  // green link in the wiki
  int *que;
  int keywordIndex;
  vector<string> keywords_;

  // n is total length, total number of nodes is at most n+1
  AhoCorasick(int n): n_(n+1), out(n_), keywordIndex(0) {
    to = new int*[n_]{};
    for (int i = 0; i < n_; i++) {
      to[i] = new int[ALPHA_SIZE]{};
    }

    link = new int[n_]{};
    next = new int[n_]{};
    que  = new int[n_]{};
  }

  ~AhoCorasick() {
    for (int i = 0; i < n_; i++) {
      delete[] to[i];
    }
    delete[] to;

    delete[] link;
    delete[] next;
    delete[] que;
  }

  void add_str(const string &s) {
    int v = 0;
    for(int i = 0; i < (int)s.length(); i++) {
      int c = s[i] - ALPHABET[0];
      if(!to[v][c]) to[v][c] = sz++;
      v = to[v][c];
    }
    out[v].insert(keywordIndex++);
    keywords_.push_back(s);
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
        if (out[link[u]].empty()) {
          next[u] = next[link[u]];
        } else {
          next[u] = link[u];
        }
        que[fi++] = u;
      }
    }
  }

  void countMatches(const string &t) {
    int q = 0;
    vector<int> cnt(keywordIndex, 0);
    for (int i = 0; i < (int)t.length(); i++) {
      int c = t[i] - ALPHABET[0];
      while (q != -1 && to[q][c] == 0) {
        q = link[q];
      }
      if (q != -1) {
        q = to[q][c];
        followDictSuffixLink(q, cnt);
      } else {
        q = 0;
      }
    }
    output(cnt);
  }

  void output(const vector<int>& cnt) const {
    int ans = 0;
    for (int i = 0; i < keywordIndex; i++) {
      ans = max(ans, cnt[i]);
    }
    printf("%d\n", ans);
    for (int i = 0; i < keywordIndex; i++) {
      if (cnt[i] == ans) {
        cout << keywords_[i] << endl;
      }
    }
  }

 private:
  void followDictSuffixLink(int q, vector<int>& cnt) const {
    while (q != 0) {
      for (int k : out[q]) {
        cnt[k]++;
      }
      q = next[q];
    }
  }
};

const int MAXN = 10600;

int main() {
  while (true) {
    int n;
    scanf("%d", &n);
    if (n == 0) break;
    AhoCorasick ac(MAXN);
    string s;
    for (int i = 0; i < n; i++) {
      cin >> s;
      ac.add_str(s);
    }
    ac.push_links();
    cin >> s;
    ac.countMatches(s);
  }

  return 0;
}
