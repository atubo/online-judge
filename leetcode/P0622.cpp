// https://leetcode.com/problems/design-circular-queue/
// 622. Design Circular Queue

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        a_ = new int[k+1]{};
        front_ = end_ = 0;
        n_ = k + 1;
    }

    ~MyCircularQueue() {
        delete[] a_;
    }

    bool isEmpty() {
        return end_ == front_;
    }

    bool isFull() {
        return (end_+1) % n_ == front_;
    }

    bool enQueue(int value) {
        if (isFull()) return false;
        a_[end_] = value;
        end_ = (end_ + 1) % n_;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;
        front_ = (front_ + 1) % n_;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return a_[front_];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return a_[(end_+n_-1)%n_];
    }

private:
    int *a_;
    int front_, end_, n_;
};

int main() {
    return 0;
}
