// https://www.luogu.org/problemnew/show/P3229
// [HNOI2013]旅行

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
int N, M;
int A[MAXN], B[MAXN], S[MAXN];
int D;

struct Node {
    int l, r, x;
} nodes[MAXN];
int tot;

int newnode(int l, int r, int x) {
    nodes[++tot] = {l, r, x};
    return tot;
}

class Queue {
    int b_ = 0, e_ = 0, len_ = 0;
public:
    void push_back(int x) {
        if (!len_) b_ = e_ = newnode(0, 0, x);
        else {
            nodes[e_].r = newnode(e_, 0, x);
            e_ = nodes[e_].r;
        }
        len_++;
    }

    bool empty() {return len_ == 0;}
    int front() {return nodes[b_].x;}
    int back() {return nodes[e_].x;}

    void pop_back() {
        e_ = nodes[e_].l;
        --len_;
    }

    void pop_front() {
        b_ = nodes[b_].r;
        --len_;
    }

    void push(int x) {
        while (!empty() && A[back()] > A[x]) pop_back();
        push_back(x);
    }
} Q[2*MAXN];

void printAns(const vector<int> &ans) {
    for (int i = 0; i < (int)ans.size()-1; i++) {
        printf("%d ", A[ans[i]]);
    }
    printf("%d\n", A[ans.back()]);
}

void solve0(vector<int> &zeros) {
    reverse(zeros.begin(), zeros.end());
    deque<int> q;
    vector<int> ans(M);
    for (int j = 0; j < M-1; j++) {
        while ((int)zeros.size() > M-1-j) {
            while (!q.empty() && A[q.back()] > A[zeros.back()]) {
                q.pop_back();
            }
            q.push_back(zeros.back());
            zeros.pop_back();
        }
        ans[j] = q.front();
        q.pop_front();
    }
    ans[M-1] = N;

    printAns(ans);
}

void solve1() {
    int last = 0;
    vector<int> ans(M);
    for (int k = 1; k <= N-M; k++) {
        Q[S[k]+N].push(k);
    }
    for (int j = 0; j < M-1; j++) {
        ans[j] = 0;
        int k = N-M+j+1;
        Q[S[k]+N].push(k);
        for (int s = max(-N, S[last]-D); s <= min(N, S[last]+D); s++) {
            if ((abs(S[N+1]-s)+M-j-2)/(M-j-1) > D) continue;
            auto &q = Q[s+N];
            while (!q.empty() && q.front() <= last) q.pop_front();
            if (!q.empty() && A[q.front()] < A[ans[j]]) {
                ans[j] = q.front();
            }
        }
        last = ans[j];
    }
    ans[M-1] = N;
    printAns(ans);
}

int main() {
    scanf("%d%d", &N, &M);
    vector<int> zeros;
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &A[i], &B[i]);
        if (B[i] == 0) B[i] = -1;
        S[i] = B[i] + S[i-1];
        if (S[i] == 0) zeros.push_back(i);
    }
    S[N+1] = S[N];
    A[0] = N+1;
    if (S[N+1] == 0 && (int)zeros.size() >= M) D = 0;
    else D = max(1, (abs(S[N+1])+M-1)/M);
    if (D == 0) solve0(zeros);
    else solve1();
    return 0;
}
