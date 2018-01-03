// https://www.luogu.org/problemnew/show/P2048
// [NOI2010]超级钢琴

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

struct Item {
    Item(int v, int p, int i): val(v), pos(p), idx(i) {}
    int val, pos, idx;
    bool operator < (const Item &other) const {
        if (val < other.val) return true;
        if (val > other.val) return false;
        return pos < other.pos;
    }
};

int N, K, L, R;

int main() {
    scanf("%d%d%d%d", &N, &K, &L, &R);
    vector<int> A(N+1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i-1];
    }
    PartitionTree pt(A);
    priority_queue<Item> pq;
    for (int i = L; i <= N; i++) {
        int val = A[i] - pt.find_by_order(max(0, i-R), i-L, 1);
        pq.push(Item(val, i, 1));
    }
    int64_t ans = 0;
    for (int i = 0; i < K; i++) {
        Item item = pq.top();
        pq.pop();
        ans += item.val;
        int pos = item.pos;
        int idx = item.idx;
        int nelem = (pos-L) - max(0, pos-R) + 1;
        if (idx < nelem) {
            int val = A[pos] - pt.find_by_order(max(0, pos-R), pos-L, idx+1);
            pq.push(Item(val, pos, idx+1));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
