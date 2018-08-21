// https://www.luogu.org/problemnew/show/P3322
// [SDOI2015]排序

#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1<<12)+10;
int64_t fac[13];
int N;
int64_t ans;

vector<int> reduce(const vector<int> seq) {
    const int n = seq.size() / 2;
    vector<int> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = seq[2*i]/2;
    }
    return ret;
}

void dfs(vector<int> seq, int moves) {
    if (seq.size() == 1) {
        ans += fac[moves];
        return;
    }
    vector<int> mismatch;
    for (size_t i = 0; i < seq.size(); i += 2) {
        int a = seq[i], b = seq[i+1];
        if (!((a & 1) == 0 && b == a + 1)) {
            mismatch.push_back(i);
        }
    }
    if (mismatch.size() > 2) return;
    if (mismatch.empty()) {
        dfs(reduce(seq), moves);
    } else if (mismatch.size() == 1) {
        int p = mismatch[0];
        swap(seq[p], seq[p+1]);
        dfs(reduce(seq), moves+1);
        swap(seq[p], seq[p+1]);
    } else {
        int p = mismatch[0], q = mismatch[1];
        int a = seq[p], b = seq[p+1], c = seq[q], d = seq[q+1];
        if ((a & 1) == 0) {
            if (c == a+1 && d == b+1) {
                swap(seq[p+1], seq[q]);
                dfs(reduce(seq), moves+1);
                swap(seq[p+1], seq[q]);
            } else if (d == a+1 && b == c+1) {
                swap(seq[p+1], seq[q+1]);
                dfs(reduce(seq), moves+1);
                swap(seq[p+1], seq[q+1]);
                swap(seq[p], seq[q]);
                dfs(reduce(seq), moves+1);
                swap(seq[p], seq[q]);
            }
        } else if ((c & 1) == 0) {
            if (a == c+1 && b == d+1) {
                swap(seq[p], seq[q+1]);
                dfs(reduce(seq), moves+1);
                swap(seq[p], seq[q+1]);
            } else if (b == c+1 && d == a+1) {
                swap(seq[p+1], seq[q+1]);
                dfs(reduce(seq), moves+1);
                swap(seq[p+1], seq[q+1]);
                swap(seq[p], seq[q]);
                dfs(reduce(seq), moves+1);
                swap(seq[p], seq[q]);
            }
        }
    }
}


int main() {
    fac[0] = 1;
    for (int i = 1; i <= 12; i++) {
        fac[i] = i * fac[i-1];
    }
    scanf("%d", &N);
    vector<int> A(1<<N);
    for (int i = 0; i < (1<<N); i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }
    dfs(A, 0);
    printf("%ld", ans);
    return 0;
}
