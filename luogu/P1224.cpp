// https://www.luogu.org/problemnew/show/P1224
// [NOI2013]向量内积

#include <bits/stdc++.h>
using namespace std;

int N, D, K;

int inner(int p, int q, int **a) {
    int ans = 0;
    for (int i = 0; i < D; i++) {
        (ans += a[p][i]*a[q][i]) %= K;
    }
    return ans;
}

void search(int p, int **a) {
    for (int i = 0; i < N; i++) {
        if (i == p) continue;
        if (inner(p, i, a) == 0) {
            int x = i, y = p;
            if (x > y) swap(x, y);
            printf("%d %d\n", x+1, y+1);
            return;
        }
    }
}

class Solution2 {
    const static int MAXN = 20010;
    const static int MAXD = 105;
public:
    Solution2() {
        line_ = new int[MAXN]{};
        tmp_  = new int[MAXD]{};
        a_ = new int*[MAXN]{};
        for (int i = 0; i < MAXN; i++) {
            a_[i] = new int[MAXD]{};
        }
    }

    ~Solution2() {
        delete[] line_;
        delete[] tmp_;
        for (int i = 0; i < MAXN; i++) {
            delete[] a_[i];
        }
        delete[] a_;
    }

    void solve() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j++) {
                scanf("%d", &a_[i][j]);
                a_[i][j] &= 1;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j++) {
                line_[i] = (line_[i] + a_[i][j]*a_[i][j]) & 1;
            }
        }

        for (int i = 0; i < D; i++) {
            for (int j = 0; j < N; j++) {
                tmp_[i] = (tmp_[i] + a_[j][i]) & 1;
            }
        }

        for (int i = 0; i < N; i++) {
            int ans = 0;
            for (int j = 0; j < D; j++) {
                ans = (ans + a_[i][j]*tmp_[j]) & 1;
            }
            if (ans != ((line_[i] + N - 1) & 1)) {
                search(i, a_);
                return;
            }
        }

        printf("-1 -1\n");
    }

private:
    int *line_; // holds C*X
    int *tmp_;  // holds (A^T)*X
    int **a_;    // N*D matrix
};

class Solution3 {
    const static int MAXN = 100010;
    const static int MAXD = 105;
public:
    Solution3() {
        line_ = new int[MAXN];
        tmp_ = new int[MAXD*MAXD];
        a_ = new int*[MAXN]{};
        for (int i = 0; i < MAXN; i++) {
            a_[i] = new int[MAXD]{};
        }
    }

    ~Solution3() {
        delete[] line_;
        delete[] tmp_;
        for (int i = 0; i < MAXN; i++) {
            delete[] a_[i];
        }
        delete[] a_;
    }

    void solve() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j++) {
                scanf("%d", &a_[i][j]);
                a_[i][j] %= 3;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j++) {
                for (int k = 0; k < D; k++) {
                    line_[i] += a_[i][j]*a_[i][j]*a_[i][k]*a_[i][k];
                }
            }
            line_[i] %= 3;
        }

        for (int j = 0; j < D; j++) {
            for (int k = 0; k < D; k++) {
                for (int i = 0; i < N; i++) {
                    tmp_[j*D+k] += a_[i][j] * a_[i][k];
                }
                tmp_[j*D+k] %= 3;
            }
        }

        for (int i = 0; i < N; i++) {
            int ans = 0;
            for (int j = 0; j < D; j++) {
                for (int k = 0; k < D; k++) {
                    ans += a_[i][j] * a_[i][k] * tmp_[j*D+k];
                }
            }
            if ((ans % 3) != ((line_[i] + N - 1) % 3)) {
                search(i, a_);
                return;
            }
        }

        printf("-1 -1\n");
    }
private:
    int *line_;
    int *tmp_;
    int **a_;
};

int main() {
    scanf("%d%d%d", &N, &D, &K);
    if (K == 2) {
        Solution2 sol;
        sol.solve();
    } else {
        Solution3 sol;
        sol.solve();
    }
    return 0;
}
