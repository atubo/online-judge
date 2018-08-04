// https://www.lintcode.com/problem/null-terminated-string/description
// 210. Null-terminated String

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverse(char *str) {
        int n = 0;
        while (str[n] != '\0') n++;
        for (int i = 0; i < n/2; i++) {
            swap(str[i], str[n-1-i]);
        }
    }
};

int main() {
    char s[20];
    cin >> s;
    Solution solution;
    solution.reverse(s);
    cout << s << endl;
    return 0;
}
