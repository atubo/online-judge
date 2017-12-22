// http://poj.org/problem?id=1465
// Multiple

#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>
using namespace std;
int N, M;

struct Node {
    Node(int prev_, int d_, int r_):prev(prev_), d(d_), r(r_) {}
    int prev, d, r;
};

void print(const vector<Node> &nodes, int x, int p) {
    string s;
    s.push_back(x + '0');
    while (p >= 0) {
        s.push_back(nodes[p].d + '0');
        p = nodes[p].prev;
    }
    reverse(s.begin(), s.end());
    printf("%s\n", s.c_str());
}

void solve(const vector<int> &X) {
    if (N == 0 || X.back() == 0) {
        printf("0\n");
        return;
    }
    vector<bool> visited(N+1);
    vector<Node> q;
    int front = 0, back = 0;
    for (int i = 0; i < M; i++) {
        int x = X[i];
        if (x == 0) continue;
        int r = x % N;
        if (r == 0) {
            printf("%d\n", x);
            return;
        }
        q.push_back(Node(-1, x, r));
        back++;
        visited[r] = true;
    }

    while (front < back) {
        const Node node = q[front++];
        for (int i = 0; i < M; i++) {
            int x = X[i];
            int r = (node.r * 10 + x) % N;
            if (r == 0) {
                print(q, x, front-1);
                return;
            }
            if (!visited[r]) {
                q.push_back(Node(front-1, x, r));
                back++;
                visited[r] = true;
            }
        }
    }
    printf("0\n");
}

int main() {
    while (scanf("%d", &N) == 1) {
        scanf("%d", &M);
        vector<int> X(M);
        for (int i = 0; i < M; i++) {
            scanf("%d", &X[i]);
        }
        sort(X.begin(), X.end());
        solve(X);
    }
    return 0;
}
