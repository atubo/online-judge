// https://leetcode.com/problems/max-stack/
// 716. Max Stack

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class MaxStack {
    struct Data {
        int x, pos;
        bool operator < (const Data &other) const {
            if (x != other.x) return x < other.x;
            return pos < other.pos;
        }
    };
public:
    MaxStack() {
        val_.resize(10010);
        mark_.resize(10010);
    }

    void push(int x) {
        val_[idx_] = {x, idx_};
        s_.insert({x, idx_});
        mark_[idx_] = true;
        idx_++;
    }

    int pop() {
        while (mark_[idx_-1] == false) {
            val_.pop_back();
            idx_--;
        }
        int ret = val_[idx_-1].x;
        s_.erase({ret, idx_-1});
        idx_--;
        return ret;
    }

    int top() {
        while (mark_[idx_-1] == false) {
            idx_--;
            val_.pop_back();
        }
        return val_[idx_-1].x;
    }

    int peekMax() {
        auto it = s_.rbegin();
        return it->x;
    }

    int popMax() {
        auto it = s_.rbegin();
        int ret = it->x;
        mark_[it->pos] = false;
        s_.erase({it->x, it->pos});
        return ret;
    }


private:
    vector<Data> val_;
    set<Data> s_;
    vector<bool> mark_;
    int idx_ = 0;

};

int main() {
    MaxStack stack;
stack.push(5); 
stack.push(1);
stack.push(5);
stack.top();
stack.popMax();
stack.top();
stack.peekMax();
stack.pop();
stack.top();
    return 0;
}
