// https://www.luogu.org/problem/show?pid=1533
// 可怜的狗狗

#include <bits/stdc++.h>
using namespace std;

class MergeTree {
private:
    int N;
    const vector<int>& A;
    vector<vector<int> > sorted;

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
            auto b = sorted[depth].begin() + left;
            auto e = sorted[depth].begin() + right + 1;
            return lower_bound(b, e, key) - b;
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
        sorted.resize(depth);
        for (int i = 0; i < depth; i++) {
            sorted[i].resize(N);
        }

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

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    MergeTree mt(A);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", mt.find_by_order(a-1, b-1, c-1));
    }
    return 0;
}
