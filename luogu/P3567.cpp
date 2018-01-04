// https://www.luogu.org/problemnew/show/P3567
// [POI2014]KUR-Couriers

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
int as[MAXN];
int tree[21][MAXN], sum[21][MAXN];


class PartitionTree {
private:
    int N;
    const vector<int>& A;

    void build(int depth, int left, int right) {
        int mid = (left + right) / 2, lm = mid - left + 1, lp = left, rp = mid + 1;
        for (int i = left; i <= mid; i++) {
            if (as[i] < as[mid]) lm--;
        }
        for (int i = left; i <= right; i++) {
            if (i == left) {
                sum[depth][i] = 0;
            } else {
                sum[depth][i] = sum[depth][i-1];
            }
            if (tree[depth][i] == as[mid]) {
                if (lm) {
                    lm--;
                    sum[depth][i]++;
                    tree[depth+1][lp++] = tree[depth][i];
                } else {
                    tree[depth+1][rp++] = tree[depth][i];
                }
            } else if (tree[depth][i] < as[mid]) {
                sum[depth][i]++;
                tree[depth+1][lp++] = tree[depth][i];
            } else {
                tree[depth+1][rp++] = tree[depth][i];
            }
        }
        if (left == right) return;
        build(depth+1, left, mid);
        build(depth+1, mid+1, right);
    }

    // find k-th element in [qleft, qright], counting from 1
    int query(int depth, int left, int right, int qleft, int qright, int k) {
        int s;  // [left, qleft) how many go to left child
        int ss; // [qleft, qright] how many go to left child

        int mid = (left + right) / 2;
        if (left == right) {
            return tree[depth][left];
        }

        if (left == qleft) {
            s = 0;
            ss = sum[depth][qright];
        } else {
            s = sum[depth][qleft-1];
            ss = sum[depth][qright] - s;
        }

        if (k <= ss) {
            return query(depth+1, left, mid, left+s, left+s+ss-1, k);
        } else {
            return query(depth+1, mid+1, right,
                         mid - left + 1 + qleft - s,
                         mid - left + 1 + qright -s - ss,
                         k - ss);
        }
    }

public:
    PartitionTree(const vector<int>& A_): A(A_) {
        N = A.size();
        int depth = 1, len = 1;
        while (len < 2*N) {
            depth++;
            len <<= 1;
        }
        for (int i = 0; i < N; i++) as[i] = A[i];
        sort(as, as+N);

        for (int i = 0; i < N; i++) {
            tree[0][i] = A[i];
        }
        build(0, 0, N-1);
    }


    // k-the element in [qleft, qright], counting from 1
    int find_by_order(int qleft, int qright, int k) {
        return query(0, 0, N-1, qleft, qright, k);
    }
};

int sorted[21][MAXN];

class MergeTree {
private:
    int N;
    const vector<int>& A;
    //vector<vector<int> > sorted;

    void build(int depth, int left, int right) {
        if (left == right) {
            sorted[depth][left] = A[left];
            return;
        }

        int mid = (left + right) / 2;
        build(depth+1, left, mid);
        build(depth+1, mid+1, right);

        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (sorted[depth+1][i] <= sorted[depth+1][j]) {
                sorted[depth][k++] = sorted[depth+1][i++];
            } else {
                sorted[depth][k++] = sorted[depth+1][j++];
            }
        }
        while (i <= mid) sorted[depth][k++] = sorted[depth+1][i++];
        while (j <= right) sorted[depth][k++] = sorted[depth+1][j++];
    }

    // find number of elements < key
    int query(int depth, int left, int right, int qleft, int qright, int key) {
        if (qright < left || qleft > right) return 0;
        if (qleft <= left && right <= qright) {
            //auto b = sorted[depth].begin() + left;
            //auto e = sorted[depth].begin() + right + 1;
            auto b = sorted[depth] + left;
            auto e = sorted[depth] + right + 1;
            //return lower_bound(b, e, key) - b;
            auto b0 = b;
            if (*b >= key) return 0;
            while (b < e - 1) {
                auto mid = b + (e - b) / 2;
                if (*mid < key) b = mid;
                else e = mid;
            }
            return e - b0;
        }

        int mid = (left + right) / 2;
        return query(depth+1, left, mid, qleft, qright, key) +
               query(depth+1, mid+1, right, qleft, qright, key);
    }

public:
    MergeTree(const vector<int>& A_): A(A_) {
        N = A.size();
        int depth = 1, len = 1;
        while (len < 2*N) {
            depth++;
            len <<= 1;
        }
#if 0
        sorted.resize(depth);
        for (int i = 0; i < depth; i++) {
            sorted[i].resize(N);
        }
#endif

        build(0, 0, N-1);
    }

    // find number of elements < key
    int order_of_key(int qleft, int qright, int key) {
        return query(0, 0, N-1, qleft, qright, key);
    }

    // k-the element in [qleft, qright], counting from 0
    int find_by_order(int qleft, int qright, int k) {
        int lo = 0, hi = N;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            int cnt = order_of_key(qleft, qright, sorted[0][mid]);
            if (cnt <= k) lo = mid;
            else hi = mid;
        }
        return sorted[0][lo];
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    PartitionTree pt(A);
    MergeTree mt(A);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        int nelem = b - a + 1;
        int nth = nelem / 2 + 1;
        int x = pt.find_by_order(a, b, nth);
        int low = mt.order_of_key(a, b, x);
        int hi  = mt.order_of_key(a, b, x+1);
        int ret = (hi - low > (b - a + 1) / 2 ? x : 0);
        printf("%d\n", ret);
    }
    return 0;
}
