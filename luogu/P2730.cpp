// https://www.luogu.org/problem/P2730
// 魔板 Magic Squares

#include <bits/stdc++.h>
using namespace std;

class Cantor {
 public:
  // members in [0, n-1]
  static int64_t encode(const vector<int>& a) {
    int64_t ret = 0;
    int64_t fac = 1;
    const int n = a.size();
    vector<bool> seen(n, false);
    for (int i = n-1; i >= 0; i--) {
      int x = a[i];
      int k = count(x, seen);
      seen[x] = true;
      ret += k * fac;
      fac *= (n-i);
    }
    return ret;
  }

  static vector<int> decode(int64_t code, int n) {
    vector<int64_t> fac(n);
    fac[0] = 1;
    for (int i = 1; i < n; i++) {
      fac[i] = fac[i-1] * i;
    }

    vector<int> ret(n);
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++) {
      int x = code / fac[n-1-i];
      code = code % fac[n-1-i];
      ret[i] = nth(x, seen);
      seen[ret[i]] = true;
    }
    return ret;
  }

 private:
  static int count(int x, const vector<bool>& seen) {
    int ret = 0;
    for (int y = 0; y < x; y++) {
      ret += seen[y];
    }
    return ret;
  }

  static int nth(int x, const vector<bool>& seen) {
    int c = 0;
    int y = 0;
    while (c < x) {
      c += (!seen[y++]);
    }
    while (seen[y]) y++;
    return y;
  }
};

struct Data {
  int d, prev, op;
  bool vis;
} D[41000];

void op1(vector<int>& b) {
  for (int i = 0; i < 4; i++) {
    swap(b[i], b[7-i]);
  }
}

void op2(vector<int>& b) {
  int p = b[3], q = b[4];
  for (int i = 3; i > 0; i--) {
    b[i] = b[i-1];
    b[7-i] = b[8-i];
  }
  b[0] = p;
  b[7] = q;
}

void op2r(vector<int>& b) {
  int p = b[0], q = b[7];
  for (int i = 0; i < 3; i++) {
    b[i] = b[i+1];
    b[7-i] = b[6-i];
  }
  b[3] = p;
  b[4] = q;
}

void op3(vector<int>& b) {
  int b1 = b[1], b2 = b[2], b5 = b[5], b6 = b[6];
  b[1] = b6;
  b[2] = b1;
  b[5] = b2;
  b[6] = b5;
}

void op3r(vector<int>& b) {
  int b1 = b[1], b2 = b[2], b5 = b[5], b6 = b[6];
  b[1] = b2;
  b[2] = b5;
  b[5] = b6;
  b[6] = b1;
}

void output(int ts) {
  printf("%d\n", D[ts].d);
  string ret;
  int s = ts;
  while (s) {
    ret.push_back('A' + D[s].op);
    s = D[s].prev;
  }
  reverse(ret.begin(), ret.end());
  printf("%s\n", ret.c_str());
}

void enqueue(queue<int>& q, int s, int s0, int op) {
  if (!D[s].vis) {
    D[s] = {D[s0].d+1, s0, op, true};
    q.push(s);
  }
}

void solve(int ts) {
  queue<int> q;
  q.push(0);
  D[0] = {0, -1, -1, true};
  while (!q.empty()) {
    int s = q.front();
    q.pop();
    if (s == ts) {
      output(ts);
      break;
    }

    vector<int> board = Cantor::decode(s, 8);

    op1(board);
    int s2 = Cantor::encode(board);
    enqueue(q, s2, s, 0);
    op1(board);

    op2(board);
    s2 = Cantor::encode(board);
    enqueue(q, s2, s, 1);
    op2r(board);

    op3(board);
    s2 = Cantor::encode(board);
    enqueue(q, s2, s, 2);
    op3r(board);
  }
}

int main() {
  vector<int> target(8);
  for (int i = 0; i < 8; i++) {
    scanf("%d", &target[i]);
    target[i]--;
  }
  int ts = Cantor::encode(target);
  solve(ts);
  return 0;
}
