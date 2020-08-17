// https://www.luogu.com.cn/problem/P5041
// [HAOI2009]求回文串

#include <bits/stdc++.h>

class FenwickTree {
public:
    // 1-indexed
    FenwickTree(int size): n_(size) {
        tree_ = new int64_t[n_+1]{};
    }

    ~FenwickTree() {
        delete[] tree_;
    }

    void clear() {
        memset(tree_, 0, (n_+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= n_) {
            tree_[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree_[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    int lowerBound(int64_t x) {
        int clz = __builtin_clz(n_);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= n_
        while (mask) {
            int t = idx + mask;
            if (t <= n_ && x > tree_[t]) {
                idx = t;
                x -= tree_[t];
            }
            mask >>= 1;
        }
        return idx+1;
    }

    int upperBound(int64_t x) {
        int p = lowerBound(x);
        if (p <= n_ && get(p) == x) p = lowerBound(x+1);
        return p;
    }

private:
    int64_t* tree_;
    const int n_;
};
const int MAXN = 1e6+10;
int prev[MAXN];
char S[MAXN];
int N;
int cnt[26];
int last[26];
int ans[MAXN], pos[MAXN];
bool vis[MAXN];

int main() {
  memset(prev, -1, sizeof(prev));
  scanf("%s", S);
  N = strlen(S);
  for (int i = 0; i < N; i++) {
    int c = S[i] - 'A';
    cnt[c]++;
    prev[i] = last[c];
    last[c] = i;
  }
  int cntOdd = 0;
  for (int i = 0; i < 26; i++) {
    if (cnt[i] & 1) cntOdd++;
  }
  if (cntOdd > 1) {
    printf("-1\n");
    return 0;
  }

  int p = 0;
  for (int i = 0; i < N/2; i++) {
    while (vis[p] || cnt[S[p]-'A'] <= 1) p++;
    int c = S[p] - 'A';
    ans[i] = p;
    ans[N-1-i] = last[c];
    vis[last[c]] = true;
    vis[p] = true;
    last[c] = prev[last[c]];
    p++;
    cnt[c] -= 2;
  }

  if (N & 1) {
    p = 0;
    while (vis[p] || cnt[S[p]-'A'] != 1) p++;
    ans[N/2] = p;
  }

  for (int i = 0; i < N; i++) {
    int x = ans[i];
    pos[x] = i + 1;
  }

  FenwickTree ft(N);
  int64_t sol = 0;
  for (int i = 0 ; i < N; i++) {
    p = pos[i];
    sol += ft.get(p+1, N);
    ft.set(p, 1);
  }
  printf("%ld\n", sol);

  return 0;
}
