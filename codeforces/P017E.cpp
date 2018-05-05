// http://codeforces.com/problemset/problem/17/E
// E. Palisection

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
    int *node;  // position i -> node index (i is 1-indexed)
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
        node = new int[L_+1]{};
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
        delete[] node;
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
        node[n_] = last;
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

const int64_t MOD = 51123987;

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    PalindromicTree pt1(s);
    reverse(s.begin(), s.end());
    PalindromicTree pt2(s);

    int64_t ans = 0;
    int open = 0;
    for (int i = 1; i <= n; i++) {
        int x1 = pt1.node[i];
        int c1 = pt1.num[x1];
        int x2 = pt2.node[n+1-i];
        int c2 = pt2.num[x2];
        open = add(open, c2);
        ans = add(ans, mul(sub(open, c1), c1));
        ans = add(ans, (int64_t(c1)*(c1-1)/2) % MOD);
        //printf("i=%d open=%d close=%d\n", i, open, c1);
        open = sub(open, c1);
    }
    printf("%lld", ans);

    return 0;
}
