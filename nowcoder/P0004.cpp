// 替换空格
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void replaceSpace(char* str, int length) {
        int nsp = 0;
        for (int i = 0; i < length; i++) {
            if (str[i] == ' ') nsp++;
        }
        int p = length-1, q = length + 2*nsp - 1;
        for (; p >=0; p--) {
            if (str[p] != ' ') str[q--] = str[p];
            else {
                str[q--] = '0';
                str[q--] = '2';
                str[q--] = '%';
            }
        }
    }
};

int main() {
    string s;
    getline(cin, s);
    char str[80] = {'\0'};;
    strcpy(str, s.c_str());
    Solution solution;
    solution.replaceSpace(str, s.length());
    cout << str << endl;
    return 0;
}
