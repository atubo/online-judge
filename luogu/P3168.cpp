// https://www.luogu.org/problemnew/show/P3168
// [CQOI2015]任务查询系统

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

struct ChairmanTree {
    struct Node {
        int l, r;
        Node *lc, *rc;
        int cnt;
        int64_t tot;
        void* operator new(size_t);

        Node(): l(0), r(0), lc(NULL), rc(NULL), cnt(0), tot(0) {}

        Node(int l_, int r_, Node *lc_, Node* rc_):
            l(l_), r(r_), lc(lc_), rc(rc_) {
                cnt = (lc ? lc->cnt : 0) + (rc ? rc->cnt : 0);
                tot = (lc ? lc->tot : 0) + (rc ? rc->tot : 0);
            }

        Node(int l_, int r_, int cnt_, int64_t tot_):
            l(l_), r(r_), lc(NULL), rc(NULL), cnt(cnt_), tot(tot_) {}

        void pushDown() {
            if (lc && rc) return;
            int mid = l + ((r - l) >> 1);
            if (!lc) lc = new Node(l, mid, (Node*)NULL, (Node*)NULL);
            if (!rc) rc = new Node(mid+1, r, (Node*)NULL, (Node*)NULL);
        }

        Node *insert(int id, int x) {
            if (id < l || id > r) return this;
            else if (id == l && id == r) {
                return new Node(l, r, this->cnt+1, this->tot + x);
            } else {
                int mid = l + ((r - l) >> 1);
                pushDown();
                if (id <= mid) {
                    return new Node(l, r, lc->insert(id, x), rc);
                } else {
                    return new Node(l, r, lc, rc->insert(id, x));
                }
            }
        }

        Node* remove(int id, int x) {
            if (id < l || id > r) return this;
            else if (id == l && id == r) {
                return new Node(l, r, this->cnt-1, this->tot - x);
            } else {
                int mid = l + ((r - l) >> 1);
                assert(lc);
                assert(rc);
                if (id <= mid) {
                    return new Node(l, r, lc->remove(id, x), rc);
                } else {
                    return new Node(l, r, lc, rc->remove(id, x));
                }
            }
        }

        int rank() const {
            return lc ? lc->cnt : 0;
        }

        int total() const {
            return tot;
        }
    };

};

ChairmanTree::Node *root[2*MAXN];

ChairmanTree::Node pool[4*MAXN*20];

void* ChairmanTree::Node::operator new(size_t) {
    static Node *P = pool;
    return P++;
}

using PII = pair<int, int>;

int M, N;
struct Task {
    int s, e, p;
} tasks[MAXN];
int setPoints[2*MAXN];
PII setPrior[2*MAXN];
int seq[2*MAXN];

struct Job {
    int s, t, p;
    bool operator < (const Job &other) const {
        if (s < other.s) return true;
        if (s > other.s) return false;
        if (t < other.t) return true;
        if (t > other.t) return false;
        return p < other.p;
    }
} jobs[2*MAXN];

int *endPoints;

using Node = ChairmanTree::Node;
int64_t query(Node *node, int k) {
    if (node->l == node->r) {
        assert(k == 1);
        return node->tot;
    }
    if (node->cnt <= k) return node->tot;
    if (node->rank() >= k) return query(node->lc, k);
    else return node->lc->tot + query(node->rc, k-node->rank());
}

int findId(int x) {
    int idx = upper_bound(setPoints, endPoints, x) - setPoints - 1;
    if (idx == -1) return -1;
    return upper_bound(seq, seq+2*M, idx) - seq - 1;
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", &tasks[i].s, &tasks[i].e, &tasks[i].p);
        tasks[i].e++;
        setPoints[2*i]   = tasks[i].s;
        setPoints[2*i+1] = tasks[i].e;
        setPrior[i] = make_pair(tasks[i].p, i);
    }
    sort(setPoints, setPoints+2*M);
    endPoints = unique(setPoints, setPoints+2*M);
    for (int i = 0; i < M; i++) {
        tasks[i].s = lower_bound(setPoints, endPoints, tasks[i].s) - setPoints;
        tasks[i].e = lower_bound(setPoints, endPoints, tasks[i].e) - setPoints;
    }
    sort(setPrior, setPrior+M);
    for (int i = 0; i < M; i++) {
        tasks[setPrior[i].second].p = i;
    }

    for (int i = 0; i < M; i++) {
        //printf("%d %d %d\n", tasks[i].s, tasks[i].e, tasks[i].p);
    }

    for (int i = 0; i < M; i++) {
        jobs[2*i] = {tasks[i].s, 0, tasks[i].p};
        jobs[2*i+1] = {tasks[i].e, 1, tasks[i].p};
    }
    sort(jobs, jobs+2*M);
    for (int i = 0; i < 2*M; i++) {
        //printf("%d %d %d\n", jobs[i].s, jobs[i].t, jobs[i].p);
        seq[i] = jobs[i].s;
    }

    root[0] = new ChairmanTree::Node(0, 2*M-1, (Node*)NULL, (Node*)NULL);
    for (int i = 0; i < 2*M; i++) {
        if (jobs[i].t == 0) {
            root[i+1] = root[i]->insert(jobs[i].p, setPrior[jobs[i].p].first);
        } else {
            root[i+1] = root[i]->remove(jobs[i].p, setPrior[jobs[i].p].first);
        }
    }

    int pre = 1;
    for (int i = 0; i < N; i++) {
        int x;
        int64_t a, b, c;
        scanf("%d%lld%lld%lld", &x, &a, &b, &c);
        int64_t k = 1 + (a * pre + b) % c;
        int id = findId(x);
        if (id == -1) {
            pre = 0;
        } else {
            pre = query(root[id+1], k);
        }
        printf("%d\n", pre);
    }

    return 0;
}
