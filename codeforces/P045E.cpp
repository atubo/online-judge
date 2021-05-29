// https://codeforces.com/problemset/problem/45/E
// Director

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N;
string A[MAXN], B[MAXN];
int C1[26], C2[26], C[26];
bool vis[MAXN];

int search(int c) {
  if (C[c] == C1[c]) {
    for (int i = 0; i < N; i++) {
      if (B[i][0] - 'A' == c && !vis[i]) {
        C1[c]--;
        C2[c]--;
        C[c]--;
        vis[i] = true;
        return i;
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (vis[i]) continue;
    int c2 = B[i][0] - 'A';
    if (c2 == c) {
      C1[c]--;
      C2[c]--;
      C[c]--;
      vis[i] = true;
      return i;
    }
    if (C2[c2] <= C1[c2]) continue;
    C1[c]--;
    C2[c2]--;
    vis[i] = true;
    return i;
  }
  assert(0);
  return -1;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }
  sort(A, A+N);
  sort(B, B+N);
  for (int i = 0; i < N; i++) {
    int c1 = A[i][0] - 'A';
    int c2 = B[i][0] - 'A';
    C1[c1]++;
    C2[c2]++;
  }
  for (int i = 0; i < 26; i++) {
    C[i] = min(C1[i], C2[i]);
  }
  vector<string> ret;
  for (int i = 0; i < N; i++) {
    int j = search(A[i][0] - 'A');
    ret.push_back(A[i] + ' ' + B[j]);
  }
  for (int i = 0; i < N; i++) {
    printf("%s", ret[i].c_str());
    if (i < N-1) printf(", ");
  }
  printf("\n");
  return 0;
}
