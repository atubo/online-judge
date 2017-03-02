// https://www.luogu.org/problem/show?pid=1026
// 统计单词个数

#include <bits/stdc++.h>
using namespace std;

int dp[210][210][41];
vector<string> dict;

int buildCount(const string& str, int i) {
    int ret = INT_MAX;
    for (const string& word: dict) {
        int len = word.length();
        if (i + len <= (int)str.length() && str.substr(i, len) == word) {
            ret = min(ret, len);
        }
    }
    return ret;
}

int main() {
    int nl, K;
    cin >> nl >> K;
    string str;
    for (int i = 0; i < nl; i++) {
        string s;
        cin >> s;
        str += s;
    }

    int s;
    cin >> s;
    dict.resize(s);
    for (int i = 0; i < s; i++) {
        cin >> dict[i];
    }

    const int N = str.length();
    vector<int> cnt(N);
    for (int i = 0; i < N; i++) {
        cnt[i] = buildCount(str, i);
    }

    for (int i = 0; i < N; i++) {
        for (int j = i; j <= N; j++) {
            for (int p = i; p < j; p++) {
                if (cnt[p] <= j - p) dp[i][j][1]++;
            }
        }
    }

    for (int k = 2; k <= K; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i; j <= N; j++) {
                for (int p = i+k-1; p <= j-1; p++) {
                    dp[i][j][k] = max(dp[i][p][k-1] + dp[p][j][1], dp[i][j][k]);
                }
            }
        }
    }

    cout << dp[0][N][K] << endl;

    return 0;
}
