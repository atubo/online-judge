// https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/
// 158. Read N Characters Given Read4 II - Call multiple times

#include <bits/stdc++.h>
using namespace std;

int read4(char *buf) {
    static int cnt = 0;
    if (cnt++ == 0) {
        buf[0] = 'a';
        buf[1] = 'b';
        return 2;
    } else {
        return 0;
    }
}

class Solution {
public:
    int read(char *buf, int n) {
        int tot = 0;
        int nr;
        while ((nr = readFromCache(buf+tot, n-tot)) > 0) {
            tot += nr;
        }
        return tot;
    }
private:
    int readFromCache(char *buf, int n) {
        if (n <= 0) return 0;
        if (cache_max_ == curr_pos_) {
            cache_max_ = read4(cache_);
            curr_pos_ = 0;
        }
        int to_read = min(n, cache_max_ - curr_pos_);
        copy(cache_ + curr_pos_, cache_ + curr_pos_ + to_read, buf);
        curr_pos_ += to_read;
        return to_read;
    }

    char cache_[4];
    int curr_pos_ = 0;
    int cache_max_ = 0;
};

int main() {
    Solution solution;
    vector<int> a = {2, 1};
    for (int i = 0; i < 2; i++) {
        char buf[10] = {'\0'};
        int nr = solution.read(buf, a[i]);
        printf("%d %s\n", nr, buf);
    }
    return 0;
}
