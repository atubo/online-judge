// https://codeforces.com/problemset/problem/23/E
// Tree

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to;
  };

  vector<int> head;
  int eidx;
  int N, M;

  Edge *E;

  Graph(int N_, int M_):N(N_), M(M_) {
    head.resize(N);
    eidx = 0;

    for (int i = 0; i < N; i++) {
      head[i] = -1;
    }

    E = new Edge[M]{};
  }

  ~Graph() {
    delete[] E;
  }

  // assume 0-indexed and no duplication
  void addEdge(int u, int v) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

class BigInt {
    // split every 9 digits
    // LSD in the first split, and so on
    static const int SPLIT_LEN = 9;
    static const int SPLIT_OVERFLOW = 1000000000;
private:
    vector<int> splits;

    static BigInt mul(const BigInt& a, const BigInt& b) {
        const int n = a.splits.size();
        const int m = b.splits.size();
        //vector<int64_t> h(n+m+10);
        int64_t h[n+m+10] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                h[i+j] += 1LL * a.splits[i] * b.splits[j];
                h[i+j+1] +=  h[i+j] / SPLIT_OVERFLOW;
                h[i+j] %= SPLIT_OVERFLOW;
            }
        }
        for (int i = 0; i < n+m+9; i++) {
            h[i+1] += h[i]/SPLIT_OVERFLOW;
            h[i] %= SPLIT_OVERFLOW;
        }

        BigInt c;
        c.splits.resize(n+m+10);
        for (int i = 0; i < n+m+10; i++) {
            c.splits[i] = h[i];
        }
        c.canonicalize();
        return c;
    }

    void canonicalize() {
        const int N = splits.size();
        for (int i = N-1; i > 0; i--) {
            if (splits[i] == 0) splits.pop_back();
            else break;
        }
    }

public:
    BigInt() {
        splits.resize(1, 0);
    }

    // x should be less than SPLIT_OVERFLOW
    BigInt(int x) {
        splits.push_back(x);
    }

    BigInt(const string& s) {
        const int n = s.length();
        int imax = (n + SPLIT_LEN - 1) / SPLIT_LEN;
        splits.resize(imax);
        for (int i = 0; i < imax; i++) {
            int start = max(0, n - (i+1)*SPLIT_LEN);
            int end   = n - i*SPLIT_LEN;
            splits[i] = 0;
            for (int j = start; j < end; j++) {
                splits[i] = splits[i] * 10 + s[j] - '0';
            }
        }
        canonicalize();
    }

    void swap(BigInt& other) {
        splits.swap(other.splits);
    }

    string toString() const {
        stringstream ss;
        ss << splits.back();
        for (int i = (int)splits.size()-2; i >= 0; i--) {
            ss.width(SPLIT_LEN);
            ss.fill('0');
            ss << splits[i];
        }
        string ret = ss.str();
        return ret;
    }

    friend BigInt operator * (const BigInt& a, const BigInt& b) {
        if (a < b) return BigInt::mul(b, a);
        else return BigInt::mul(a, b);
    }

    BigInt& operator += (const BigInt &b) {
        const int N = splits.size();
        const int M = b.splits.size();

        const int L = max(N, M);

        splits.resize(L);

        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? splits[i] : 0) + (i < M ? b.splits[i] : 0) + carry;
            splits[i] = d % SPLIT_OVERFLOW;
            carry = (d >= SPLIT_OVERFLOW);
        }

        if (carry) {
            splits.push_back(1);
        }

        return *this;
    }

    friend BigInt operator + (const BigInt& a, const BigInt& b) {
        BigInt ret = a;
        ret += b;
        return ret;
    }

    friend bool operator <= (const BigInt& a, const BigInt& b) {
        return (a < b || a == b);
    }

    friend bool operator < (const BigInt& a, const BigInt& b) {
        if (a.splits.size() < b.splits.size()) return true;
        if (a.splits.size() > b.splits.size()) return false;

        for (int i = (int)a.splits.size()-1; i >= 0; i--) {
            if (a.splits[i] < b.splits[i]) return true;
            if (a.splits[i] > b.splits[i]) return false;
        }

        return false;
    }

    friend bool operator == (const BigInt& a, const BigInt& b) {
        return a.splits == b.splits;
    }
};

const int MAXN = 705;
int N;
//BigInt dp[MAXN][MAXN];
BigInt* dp[MAXN];
BigInt tmp[MAXN];
int sz[MAXN];

void dfs1(const Graph& g, int u, int fa) {
  sz[u] = 1;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs1(g, v, u);
      sz[u] += sz[v];
    }
  }
}

void dfs2(const Graph& g, int u, int fa) {
  dp[u] = new BigInt[sz[u]+1];
  dp[u][1] = 1;
  int currSz = 1;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs2(g, v, u);
      for (int i = 1; i <= currSz + sz[v]; i++) tmp[i] = 0;
      for (int s = 1; s <= currSz; s++) {
        if (dp[u][s] == 0) continue;
        for (int k = 1; k <= sz[v]; k++) {
          if (dp[v][k] == 0) continue;
          tmp[s] = max(tmp[s], dp[u][s] * dp[v][k] * k);
          tmp[s+k] = max(tmp[s+k], dp[u][s] * dp[v][k]);
        }
      }
      currSz += sz[v];
      for (int i = 1; i <= currSz; i++) dp[u][i].swap(tmp[i]);
    }
  }
}
        
int main() {
  scanf("%d", &N);
  Graph g(N, 2*(N-1));
  for (int i = 0; i < N-1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    g.addEdge(a, b);
    g.addEdge(b, a);
  }
  dfs1(g, 0, -1);
  dfs2(g, 0, -1);
  BigInt ans = 0;
  for (int i = 1; i <= sz[0]; i++) {
    ans = max(ans, dp[0][i] * i);
  }
  cout << ans.toString() << endl;
  return 0;
}
