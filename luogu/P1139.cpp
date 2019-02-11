// https://www.luogu.org/problemnew/show/P1139
// 单向双轨道

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30;
int N;
int A[MAXN];
int maxd;
int stid[MAXN];

struct Op {
    int train, source, target;
    void print() const {
        printf("%c %c %c\n", 'a'+train, 'A'+source, 'A'+target);
    }
} op[3*MAXN];

vector<stack<int>> st(2);

void reset() {
    while (!st[0].empty()) st[0].pop();
    while (!st[1].empty()) st[1].pop();
    memset(stid, -1, sizeof(stid));
}

void dispatch(int id, int s, int t, int depth) {
    op[depth] = {id, s, t};
    stid[id] = -1;
    if (s == 1 || s == 2) {
        assert(st[s-1].top() == id);
        st[s-1].pop();
    }
    if (t == 1 || t == 2) {
        st[t-1].push(id);
        stid[id] = t-1;
    }
}

void undispatch(int id, int s, int t, int depth) {
    stid[id] = -1;
    if (s == 1 || s == 2) {
        st[s-1].push(id);
        stid[id] = s-1;
    }
    if (t == 1|| t == 2) {
        assert(st[t-1].top() == id);
        st[t-1].pop();
    }
}

bool check(int target) {
#if 1
    stack<int> cpy = st[1];
    for (int i = target; i >= 0; i--) {
        if (!cpy.empty() && cpy.top() == A[i]) cpy.pop();
    }
    return cpy.empty();
#endif
}

bool dfs(int source, int target, int depth) {
    if (depth > maxd) return false;
    if (target < 0) return true;
    int x = A[target];
    if (source == x) {
        dispatch(source, 0, 3, depth);
        if (dfs(source-1, target-1, depth+1)) return true;
        undispatch(source, 0, 3, depth);
        return false;
    }
    if (source >= 0) {
        dispatch(source, 0, 1, depth);
        if (dfs(source-1, target, depth+1)) return true;
        undispatch(source, 0, 1, depth);
        dispatch(source, 0, 2, depth);
        if (dfs(source-1, target, depth+1)) return true;
        undispatch(source, 0, 2, depth);
    }

    if (!st[0].empty()) {
        int tp = st[0].top();
        if (tp == x) {
            dispatch(x, 1, 3, depth);
            if (dfs(source, target-1, depth+1)) return true;
            undispatch(x, 1, 3, depth);
            return false;
        }
        dispatch(tp, 1, 2, depth);
        if (check(target) && dfs(source, target, depth+1)) return true;
        undispatch(tp, 1, 2, depth);
    }
    if (!st[1].empty()) {
        int tp = st[1].top();
        if (tp != x) return false;
        dispatch(x, 2, 3, depth);
        if (check(target) && dfs(source, target-1, depth+1)) return true;
        undispatch(x, 2, 3, depth);
        return false;
    }
    return false;

}

int main() {
    scanf("%d", &N);
    string s;
    cin >> s;
    for (int i = 0; i < N; i++) {
        A[i] = s[i] - 'a';
    }
    bool ret = false;
    for (maxd = 1; maxd <= 3*N; maxd++) {
        reset();
        ret = dfs(N-1, N-1, 0);
        if (ret) {
            for (int i = 0; i < maxd; i++) {
                op[i].print();
            }
            break;
        }
    }
    if (!ret) printf("NO");
    return 0;
}
