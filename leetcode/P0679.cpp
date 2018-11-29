// https://leetcode.com/problems/24-game/
// 679. 24 Game

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

struct Rational {
    int p, q;
    Rational(int _p, int _q) {
        p = _p;
        q = _q;
        normalize();
    }

    void normalize() {
        if (p == 0) q = 1;
        int g = gcd(abs(p), q);
        p /= g;
        q /= g;
    }

    bool operator < (const Rational &other) const {
        if (p < other.p) return true;
        if (p > other.p) return false;
        return q < other.q;
    }

    bool operator == (const Rational &other) const {
        return p == other.p && q == other.q;
    }

    bool operator != (const Rational &other) const {
        return !(*this == other);
    }
};

Rational add(const Rational &a, const Rational &b) {
    int q = a.q * b.q;
    int p = a.p * b.q + a.q * b.p;
    return Rational(p, q);
}

Rational sub(const Rational &a, const Rational &b) {
    int q = a.q * b.q;
    int p = a.p * b.q - a.q * b.p;
    return Rational(p, q);
}

Rational mul(const Rational &a, const Rational &b) {
    int q = a.q * b.q;
    int p = a.p * b.p;
    return Rational(p, q);
}

Rational div(const Rational &a, const Rational &b) {
    int q = a.q * b.p;
    int p = a.p * b.q;
    return Rational(p, q);
}

class Solution {
public:
    bool judgePoint24(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        do {
            auto s = solve(nums, 0, 3);
            if (s.count(Rational(24, 1)) > 0) return true;
        } while (next_permutation(nums.begin(), nums.end()));
        return false;
    }

private:
    set<Rational> solve(const vector<int> &nums, int l, int r) {
        if (l == r) return {Rational(nums[l], 1)};
        set<Rational> ret;
        for (int i = l; i <= r-1; i++) {
            auto left = solve(nums, l, i);
            auto right = solve(nums, i+1, r);
            for (auto oprand1: left) {
                for (auto oprand2: right) {
                    auto x = add(oprand1, oprand2);
                    ret.insert(x);
                    x = sub(oprand1, oprand2);
                    ret.insert(x);
                    x = mul(oprand1, oprand2);
                    ret.insert(x);
                    if (oprand2 != Rational(0, 1)) {
                        x = div(oprand1, oprand2);
                        ret.insert(x);
                    }
                }
            }
        }
        return ret;
    }
};

int main() {
    vector<int> a(4);
    scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
    Solution solution;
    cout << solution.judgePoint24(a) << endl;
    return 0;
}
