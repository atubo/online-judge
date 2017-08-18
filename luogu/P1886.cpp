// https://www.luogu.org/problem/show?pid=1886
// 滑动窗口

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
int N, K;
int A[MAXN];

void solve(function<bool(int, int)> cmp) {
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < K; i++) {
        while (!dq.empty() && !cmp(A[dq.back()], A[i])) dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(A[dq.front()]);
    for (int i = K; i < N; i++) {
        while (!dq.empty() && !cmp(A[dq.back()], A[i])) dq.pop_back();
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i-K) dq.pop_front();
        ans.push_back(A[dq.front()]);
    }
    for (int i = 0; i < (int)ans.size(); i++) {
        printf("%d", ans[i]);
        if (i < (int)ans.size()-1) printf(" ");
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    solve([](int x, int y){return x < y;});
    solve([](int x, int y){return x > y;});
    return 0;
}
