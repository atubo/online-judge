// https://codeforces.com/problemset/problem/54/D
// Writing a Song

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N, K, M;
int A[MAXN];
int P[MAXN];
char S[MAXN];

struct Constraint {
  int start;
  vector<int> fbd;
  bool violated(int pos) const {
    if (start > pos || start + int(fbd.size()) - 1 > pos) return false;
    for (int i = start; i < start + int(fbd.size()); i++) {
      if (A[i] != fbd[i-start]) return false;
    }
    return true;
  }
};

bool fillOccurrence() {
  for (int i = 0; i < N-M+1; i++) {
    if (S[i] == '1') {
      for (int j = 0; j < M; j++) {
        if (A[i+j] == -1) A[i+j] = P[j];
        if (A[i+j] != P[j]) return false;
      }
    }
  }
  return true;
}

bool verifyNoOccurrence(int pos) {
  for (int i = 0; i < M; i++) {
    if (A[pos+i] == -1 || A[pos+i] != P[i]) return true;
  }
  return false;
}

bool dfs(int left, int right, const vector<Constraint>& constraints) {
  if (left == right) {
    return true;
  }
  for (int c = 0; c < K; c++) {
    A[left] = c;
    bool ok = true;
    for (const auto& cs : constraints) {
      if (cs.violated(left)) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    ok = dfs(left+1, right, constraints);
    if (ok) return true;
  }
  return false;
}

optional<Constraint> build(int pos, int left, int right) {
  for (int i = pos; i < pos + M; i++) {
    if (A[i] != -1 && A[i] != P[i-pos]) return nullopt;
  }
  int start = max(left, pos);
  vector<int> fbd;
  for (int i = start; i < min(right, pos+M); i++) {
    fbd.push_back(P[i-pos]);
  }
  return Constraint{.start = start, .fbd = fbd};
}

bool fillNoOccurrence(int left, int right) {
  vector<Constraint> constraints;
  for (int i = left - M + 1; i < right; i++) {
    if (S[i] == '0') {
      auto c = build(i, left, right);
      if (c) {
        constraints.push_back(c.value());
      }
    }
  }

  return dfs(left, right, constraints);
}

int main() {
  memset(A, -1, sizeof(P));
  scanf("%d%d", &N, &K);
  scanf("%s", S);
  M = strlen(S);
  for (int i = 0; i < M; i++) {
    P[i] = S[i] - 'a';
  }
  scanf("%s", S);
  bool ok = fillOccurrence();
  if (!ok) {
    printf("No solution\n");
    return 0;
  }

  for (int i = 0; i < N-M+1; i++) {
    if (S[i] == '0') {
      ok = verifyNoOccurrence(i);
      if (!ok) {
        printf("No solution\n");
        return 0;
      }
    }
  }

  {
    int p = 0;
    while (true) {
      while (p < N && A[p] != -1) p++;
      if (p == N) break;
      int q = p + 1;
      while (q < N && A[q] == -1) q++;
      ok = fillNoOccurrence(p, q);
      if (!ok) {
        printf("No solution\n");
        return 0;
      }
      p = q;
    }
  }

  for (int i = 0; i < N; i++) {
    S[i] = 'a' + A[i];
  }
  S[N] = '\0';
  printf("%s\n", S);


  return 0;
}
