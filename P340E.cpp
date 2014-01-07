#include <iostream>
#include <map>
#include <cassert>
#include <cstdio>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) a[i]--;
    }

    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    map<int, int> chains;
    int closed = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] || a[i] == -1) continue;
        int x = i;
        int sz = 0;
        while (a[x] != -1 && !visited[x]) {
            visited[x] = true;
            sz++;
            x = a[x];
        }
        if (x == i) {
            closed++;
            chains[i] = sz;
        }
        else if (a[x] == -1) {
            chains[i] = sz + 1;
        } else {
            assert(chains.find(x) != chains.end());
            sz += chains[x];
            chains[i] = sz;
            chains.erase(x);
        }
    }

    int freeNode = n;
    for (pair<int, int> p: chains) {
        freeNode -= p.second;
    }
    int partial = chains.size() - closed;

    const int MOD = 1000000007;
    int choose[n+1][n+1];
    for (int i = 1; i <= n; i++) {
        choose[i][0] = 1;
        for (int j = 1; j <= i/2; j++) {
            choose[i][j] = (choose[i-1][j-1] + choose[i-1][j]) % MOD;
        }
        for (int j = i/2+1; j <= i; j++) {
            choose[i][j] = choose[i][i-j];
        }
    }

    int fact[n+1];
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * (int64_t) i) % MOD;
    }

    int perm[n+1];
    perm[0] = 1;
    for (int i = 1; i <= freeNode + partial; i++) {
        perm[i] = fact[i];
        for (int j = 1; j <= i; j++) {
            perm[i] = (perm[i] + MOD - (choose[i][j] * (int64_t)perm[i-j]) % MOD)
                       % MOD;
        }
    }

    int result = (freeNode == 0 ? 0 : perm[freeNode]);
    for (int i = 1; i <= partial; i++) {
        result = (result +
                  choose[partial][i] * (int64_t)perm[freeNode + i] % MOD) % MOD;
    }

    printf("%d\n", result);


    return 0;
}

