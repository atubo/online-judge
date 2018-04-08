// https://www.luogu.org/problem/show?pid=1903
// [国家集训队]数颜色

#include <bits/stdc++.h>
using namespace std;

struct Action {
    int type, x, y;
};

const int MAXN = 10010;
int N, M;
int A[MAXN];
Action actions[MAXN];
vector<int> sorted;

int order(int x) {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
}

class MoWithUpdate {
    struct Query {
        int l, r, t, id;
        int bl_id, br_id;

        bool operator < (const Query &other) const {
            if (bl_id < other.bl_id) return true;
            if (bl_id > other.bl_id) return false;
            if (br_id < other.br_id) return true;
            if (br_id > other.br_id) return false;
            if (t < other.t) return true;
            if (t > other.t) return false;
            return id < other.id;
        }
    };

private:
    int N;
    int BLOCK_SIZE;
    vector<Query> queries;
    int updIdx = 0;
    int id = 0;
    int nowAns = 0, lcurr = 0, rcurr = 0, tcurr = 0;

    // custmize the following
    struct Update {
        int x, c, cp;
    };
    vector<Update> updates;

    void move(int pos, int sign) {
        int c = color[pos];
        if (sign == -1) {
            if (--cnt[c] == 0) nowAns--;
        } else {
            if (++cnt[c] == 1) nowAns++;
        }
    }

    void moveTime(int t, int sign) {
        int x = updates[t].x;
        int c = updates[t].c;
        int cp = updates[t].cp;
        if (lcurr <= x && x < rcurr) {
            if (sign == 1) {
                if (--cnt[cp] == 0) nowAns--;
                if (++cnt[c] == 1) nowAns++;
            } else {
                if (--cnt[c] == 0) nowAns--;
                if (++cnt[cp] == 1) nowAns++;
            }
        }
        color[x] = (sign == 1 ? c : cp);
    }

public:
    vector<int> ans;

    vector<int> color;
    vector<int> cnt;

public:
    MoWithUpdate(int N_): N(N_) {
        BLOCK_SIZE = int(ceil(pow(N, 2.0/3)));
    }

    void addQuery(int l, int r) {
        int bl_id = l/BLOCK_SIZE;
        int br_id = r/BLOCK_SIZE;
        Query q{l, r, updIdx, id++, bl_id, br_id};
        queries.push_back(q);
    }

    void addUpdate(int x, int c, int cp) {
        Update upd{x, c, cp};
        updates.push_back(upd);
        updIdx++;
    }

    void solve() {
        ans.resize(queries.size());
        sort(queries.begin(), queries.end());
        for (const auto &q: queries) {
            while (tcurr < q.t) moveTime(tcurr++, 1);
            while (tcurr > q.t) moveTime(--tcurr, -1);
            while (lcurr < q.l) move(lcurr++, -1);
            while (lcurr > q.l) move(--lcurr, 1);
            while (rcurr < q.r) move(rcurr++, 1);
            while (rcurr > q.r) move(--rcurr, -1);
            ans[q.id] = nowAns;
        }
    }
};

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sorted.push_back(A[i]);
    }
    for (int i = 0; i < M; i++) {
        char s[10];
        int x, y;
        scanf("%s%d%d", s, &x, &y);
        int t = (s[0] == 'Q' ? 0 : 1);
        actions[i] = {t, x, y};
        if (t == 1) sorted.push_back(y);
    }
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    MoWithUpdate mo(N);
    for (int i = 0; i < N; i++) {
        mo.color.push_back(order(A[i]));
    }
    mo.cnt.resize(sorted.size(), 0);

    for (int i = 0; i < M; i++) {
        int type = actions[i].type;
        int x = actions[i].x;
        int y = actions[i].y;
        if (type == 0) {
            mo.addQuery(x-1, y);
        } else {
            mo.addUpdate(x-1, order(y), order(A[x-1]));
            A[x-1] = y;
        }
    }

    mo.solve();
    for (int x: mo.ans) {
        printf("%d\n", x);
    }

    return 0;
}
