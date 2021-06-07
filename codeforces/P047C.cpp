// https://codeforces.com/problemset/problem/47/C
// Crossword

#include <bits/stdc++.h>
using namespace std;

char S[6][32];
int L[6];
vector<string> mins;
vector<int> ans;

bool verify(const vector<int>& w) {
  if (L[w[3]] != L[w[0]] + L[w[4]] - 1) return false;
  if (L[w[2]] != L[w[1]] + L[w[5]] - 1) return false;
  int h1 = L[w[1]];
  int h2 = L[w[2]];
  int l1 = L[w[0]];
  int l2 = L[w[3]];
  if (S[w[0]][0] != S[w[1]][0]) return false;
  if (S[w[0]][l1-1] != S[w[2]][0]) return false;
  if (S[w[1]][h1-1] != S[w[3]][0]) return false;
  if (S[w[2]][h1-1] != S[w[3]][l1-1]) return false;
  if (S[w[2]][h2-1] != S[w[4]][0]) return false;
  if (S[w[3]][l2-1] != S[w[5]][0]) return false;
  if (S[w[4]][l2-l1] != S[w[5]][h2-h1]) return false;

  return true;
}

vector<string> build(const vector<int>& w) {
  vector<string> ret;
  int h1 = L[w[1]];
  int h2 = L[w[2]];
  int l1 = L[w[0]];
  int l2 = L[w[3]];
  string line = S[w[0]];
  for (int i = 0; i < l2-l1; i++) {
    line += '.';
  }
  ret.push_back(line);
  for (int i = 1; i < h1-1; i++) {
    line = S[w[1]][i];
    for (int j = 0; j < l1-2; j++) {
      line += '.';
    }
    line += S[w[2]][i];
    for (int j = 0; j < l2-l1; j++) {
      line += '.';
    }
    ret.push_back(line);
  }
  ret.emplace_back(S[w[3]]);
  for (int i = h1; i < h2-1; i++) {
    line.clear();
    for (int j = 0; j < l1-1; j++) {
      line += '.';
    }
    line += S[w[2]][i];
    for (int j = 0; j < l2-l1-1; j++) {
      line += '.';
    }
    line += S[w[5]][i-h1+1];
    ret.push_back(line);
  }
  line.clear();
  for (int j = 0; j < l1-1; j++) {
    line += '.';
  }
  line += S[w[4]];
  ret.push_back(line);
  return ret;
}

void search(int p, vector<int>& w) {
  if (p == 6) {
    if (verify(w)) {
      vector<string> f = build(w);
      if (mins.empty() || f < mins) {
        mins = f;
        ans = w;
      }
    }
    return;
  }
  int mask = 0;
  for (int x : w) {
    mask |= 1 << x;
  }
  for (int i = 0; i < 6; i++) {
    if (((mask >> i) & 1) == 0) {
      w.push_back(i);
      search(p+1, w);
      w.pop_back();
    }
  }
}

int main() {
  for (int i = 0; i < 6; i++) {
    scanf("%s", S[i]);
    L[i] = strlen(S[i]);
  }
  vector<int> w;
  search(0, w);
  if (ans.empty()) {
    printf("Impossible\n");
    return 0;
  }
  for (const auto& line : mins) {
    printf("%s\n", line.c_str());
  }

  return 0;
}
