// https://leetcode.com/problems/logger-rate-limiter/description/
// 359. Logger Rate Limiter

#include <bits/stdc++.h>
using namespace std;

class Logger {
public:
    Logger() {}

    bool shouldPrintMessage(int timestamp, string message) {
        if (last.count(message) > 0 && last[message] > timestamp - 10) {
            return false;
        } else {
            last[message] = timestamp;
            return true;
        }
    }
private:
    map<string, int> last;
};

int main() {
    return 0;
}
