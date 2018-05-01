// https://www.luogu.org/problemnew/show/P1659
// [国家集训队]拉拉队排练

#include <bits/stdc++.h>
using namespace std;

class PalindromicTree {
public:
    const static int ALPHASIZE = 26;
    const int L_;
    int** next;
    int *fail;
    int *cnt;
    int *num;
    int *len;
    int *S;
    int last;
    int n_;
    int p_;

private:
    int newnode(int l) {
        cnt[p_] = 0;
        num[p_] = 0;
        len[p_] = l;
        return p_++;
    }

    void alloc() {
        next = new int*[L_+2];
        for (int i = 0; i < L_+2; i++) {
            next[i] = new int[ALPHASIZE]{};
        }
        fail = new int[L_+2]{};
        cnt = new int[L_+2]{};
        num = new int[L_+2]{};
        len = new int[L_+2]{};
        S = new int[L_+2]{};
    }

    void dealloc() {
        for (int i = 0; i < L_+2; i++) {
            delete[] next[i];
        }
        delete[] next;
        delete[] fail;
        delete[] cnt;
        delete[] num;
        delete[] len;
        delete[] S;
    }

    void init() {
        p_ = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n_ = 0;
        S[n_] = -1;
        fail[0] = 1;
    }

    int get_fail(int x) {
        while (S[n_-len[x]-1] != S[n_]) x = fail[x];
        return x;
    }

    void add(int c) {
        c -= 'a';
        S[++n_] = c;
        int cur = get_fail(last);
        if (!next[cur][c]) {
            int now = newnode(len[cur] + 2);
            fail[now] = next[get_fail(fail[cur])][c];
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }

    void count() {
        for (int i = p_-1; i >= 0; --i) {
            cnt[fail[i]] += cnt[i];
        }
    }


public:
    PalindromicTree(const string &s): L_(s.length()) {
        alloc();
        init();
        for (char c: s) {
            add(c);
        }

        count();
    }

    ~PalindromicTree() {
        dealloc();
    }
};

const int MOD = 19930726;

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t power(int64_t x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x % MOD;
    int64_t xp = power(x, n/2);
    int64_t ans = mul(xp, xp);
    if (n & 1) ans = mul(ans, x);
    return ans;
}


int N, K;

struct Node {
    int len, cnt;
    bool operator < (const Node &other) const {
        if (len > other.len) return true;
        if (len < other.len) return false;
        return cnt > other.cnt;
    }
};

int main() {
    scanf("%d%d", &N, &K);
    string s;
    cin >> s;
    PalindromicTree pt(s);
    int64_t ans = 1;
    vector<Node> nodes;
    for (int i = 2; i <= pt.p_-1; i++) {
        nodes.push_back({pt.len[i], pt.cnt[i]});
    }
    sort(nodes.begin(), nodes.end());
    for (const auto &node: nodes) {
        if (node.len & 1) {
            if (node.cnt >= K) {
                ans = mul(ans, power(node.len, K));
                K = 0;
                break;
            } else {
                ans = mul(ans, power(node.len, node.cnt));
                K -= node.cnt;
            }
        }
    }
    if (K > 0) {
        printf("-1");
    } else {
        printf("%lld", ans);
    }
    return 0;
}
