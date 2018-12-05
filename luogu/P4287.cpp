// https://www.luogu.org/problemnew/show/P4287
// [SHOI2011]双倍回文

#include <bits/stdc++.h>
using namespace std;

// see https://www.felix021.com/blog/read.php?2040
struct Manacher {
    const int length_;
    // p[i] stores maximum radius from position i (including i)
    // in the *modified* string (including spaces between letters)
    // note place before the first char is 1, first char is 2
    // second char is 4, etc.
    int *p;
    char *s;
    int *maxlen;

    Manacher(const string &sin):length_(sin.length()) {
        alloc();

        // put special charaters at the begining and between letters
        s[0] = '$';
        s[1] = '#';
        for (int i = 0; i < (int)sin.length(); i++) {
            s[i*2+2] = sin[i];
            s[i*2+3] = '#';
        }

        int mx = 0, id = 0;
        for (int i = 1; s[i] != '\0'; i++) {
            p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
            while (s[i+p[i]] == s[i-p[i]]) p[i]++;
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
    }

    ~Manacher() {
        dealloc();
    }

    // some utility functions
    // find for each position the maximum length of the palindrom start there
    // note the index starts from 0
    void calcMaxlen() {
        for (int i = 1; s[i] != '\0'; i++) {
            int pos = (i - p[i]) / 2;
            maxlen[pos] = max(maxlen[pos], p[i]-1);
        }
        for (int i = 1; i < length_; i++) {
            maxlen[i] = max(maxlen[i-1]-2, maxlen[i]);
        }
    }

private:
    void alloc() {
        p = new int[2*length_+3]{};
        s = new char[2*length_+3]{};
        maxlen = new int[length_+1]{};
    }

    void dealloc() {
        delete[] p;
        delete[] s;
        delete[] maxlen;
    }
};

const int MAXN = 5e5+10;
int N;
int A[MAXN], B[MAXN], st[MAXN][20];

void build() {
    for (int i = 1; i < N; i++) {
        st[i][0] = B[i];
    }
    int len = 1;
    for (int k = 1; k < 20; k++) {
        len *= 2;
        for (int i = 1; i < N; i++) {
            if (i+len > N) break;
            st[i][k] = max(st[i][k-1], st[i+len/2][k-1]);
        }
    }
}

int query(int l, int r) {
    int k = 0;
    while (l + (1<<(k+1)) < r+1) k++;
    return max(st[l][k], st[r+1-(1<<k)][k]);
}

int search(int x0, int r) {
    if (r == 0) return 0;
    if (query(x0+1, x0+r) < -x0) return 0;
    if (B[x0+r] >= -x0) return r;
    int lo = x0+1, hi = x0+r;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (query(mid, x0+r)  >= -x0) lo = mid;
        else hi = mid;
    }
    return lo - x0;
}

int main() {
    scanf("%d", &N);
    string s;
    cin >> s;
    Manacher manacher(s);
    for (int i = 1; i < N; i++) {
        A[i] = (manacher.p[2*i+1] - 1) / 2;
        B[i] = A[i] - i;
    }

    build();

    int ans = 0;
    for (int i = 1; i < N-1; i++) {
        int x = search(i, A[i]/2);
        ans = max(ans, x);
    }

    printf("%d\n", ans*4);
    return 0;
}
