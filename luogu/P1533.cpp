// https://www.luogu.org/problem/show?pid=1533
// 可怜的狗狗

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
        int mid = (left + right) / 2, lp = left, rp = mid + 1;
        for (int i = left; i <= right; i++) {
            if (i == left) {
                sum[depth][i] = 0;
            } else {
                sum[depth][i] = sum[depth][i-1];
            }
            if (tree[depth][i] <= as[mid]) {
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


    // k-the element in [qleft, qright], counting from 0
    int find_by_order(int qleft, int qright, int k) {
        return query(0, 0, N-1, qleft, qright, k);
    }
};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    PartitionTree pt(A);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", pt.find_by_order(a-1, b-1, c));
    }
    return 0;
}
