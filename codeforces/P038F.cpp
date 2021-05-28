// https://codeforces.com/problemset/problem/38/F
// Smart Boy

#include <bits/stdc++.h>
using namespace std;

const int M = 1e9 + 7;
const int B = 233;

struct Reward {
  bool win = false;
  int score1 = 0, score2 = 0;
};

int hashStr(const string& s) {
  int res = 0;
  for (int i = 0; i < (int)s.length(); i++) {
    res = (1LL * res * B + s[i]) % M;
  }
  return res;
}

int N;
vector<string> S;
unordered_map<int, int> R;
unordered_map<int, Reward> D;
int P[32];

void score(const string& s, int c) {
  int t = 0, m = 0;
  for (int i = 0; i < (int)s.length(); i++) {
    t += s[i] - 'a' + 1;
    m = max(m, s[i] - 'a' + 1);
  }
  R[hashStr(s)] = t * m + c;
}

void build() {
  map<string, set<int>> seen;
  for (int i = 0; i < N; i++) {
    int l = S[i].length();
    for (int p = 0; p < l; p++) {
      for (int q = p; q < l; q++) {
        string s = S[i].substr(p, q-p+1);
        seen[s].insert(i);
      }
    }
  }
  for (const auto& [s, c] : seen) {
    score(s, c.size());
  }
  P[0] = 1;
  for (int i = 1; i <= 30; i++) {
    P[i] = (1LL * P[i-1] * B) % M;
  }
}

void merge(Reward& s, const Reward& t, int x) {
  if (t.win && !s.win) {
    if (t.score2 + x > s.score1) {
      s.score1 = t.score2 + x;
      s.score2 = t.score1;
    } else if (t.score2 + x == s.score1) {
      s.score2 = min(s.score2, t.score1);
    }
  }
  if (!t.win) {
    if (!s.win) {
      s.win = true;
      s.score1 = t.score2 + x;
      s.score2 = t.score1;
    } else {
      if (t.score2 + x > s.score1) {
        s.score1 = t.score2 + x;
        s.score2 = t.score1;
      } else if (t.score2 + x == s.score1) {
        s.score2 = min(s.score2, t.score1);
      }
    }
  }
}

Reward solve(int s, int d) {
  if (D.count(s) > 0) return D[s];
  Reward& ret = D[s];
  for (char c = 'a'; c <= 'z'; c++) {
    int t = (1LL * s * B + c) % M;
    if (R.count(t) > 0) {
      int x = R[t];
      Reward rt = solve(t, d+1);
      merge(ret, rt, x);
    }
    t = (1LL * c * P[d] + s) % M;
    if (R.count(t) > 0) {
      int x = R[t];
      Reward rt = solve(t, d+1);
      merge(ret, rt, x);
    }
  }
  return ret;
}

int main() {
  scanf("%d", &N);
  S.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i];
  }

  build();
  Reward r = solve(0, 0);
  printf("%s\n%d %d\n", r.win ? "First" : "Second", r.score1, r.score2);

  return 0;
}
