// https://www.luogu.org/problem/show?pid=1801
// 黑匣子_NOI导刊2010提高（06）

#include <bits/stdc++.h>
using namespace std;


class PartitionTree {
private:
    int N;
    const vector<int>& A;
    vector<int> as;
    vector<vector<int> > tree;
    vector<vector<int> > sum;

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
        tree.resize(depth);
        for (int i = 0; i < depth; i++) {
            tree[i].resize(N);
        }

        sum.resize(depth);
        for (int i = 0;i < depth; i++) {
            sum[i].resize(N);
        }

        as = A;
        sort(as.begin(), as.end());

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

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    vector<int> A(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[i]);
    }

    PartitionTree pt(A);

    for (int i = 0; i < N; i++) {
        int u;
        scanf("%d", &u);
        printf("%d\n", pt.find_by_order(0, u-1, i+1));
    }
    return 0;
}
