// https://www.luogu.org/problem/show?pid=2278
// [HNOI2003]操作系统

#include <bits/stdc++.h>
using namespace std;

struct Task {
    Task(int id_, int priority_, int arrival_, int start_, int remain_)
        :id(id_), priority(priority_), arrival(arrival_), start(start_),
        remain(remain_) {}
    int id;
    int priority;
    int arrival;
    int start, remain;
    bool operator < (const Task &other) const {
        if (priority < other.priority) return true;
        if (priority > other.priority) return false;
        return (arrival > other.arrival);
    }

    void print() {
        printf("id=%d start=%d remain=%d\n", id, start, remain);
    }
};

using PQ = priority_queue<Task>;

void start(Task &task, int curr) {
    assert(task.start == -1);
    task.start = curr;
}

void stop(Task &task, int curr) {
    assert(task.start >= 0 && task.start + task.remain > curr);
    task.remain -= curr - task.start;
    task.start = -1;
}

int main() {
    int id, arrival, duration, priority;
    int curr = 0;
    PQ pq;
    while (scanf("%d%d%d%d", &id, &arrival, &duration, &priority) == 4) {
        curr = arrival;
        while (!pq.empty() && pq.top().start + pq.top().remain <= curr) {
            const Task task = pq.top();
            printf("%d %d\n", task.id, task.start + task.remain);
            pq.pop();
            if (!pq.empty()) {
                start(const_cast<Task&>(pq.top()), task.start + task.remain);
            }
        }
        if (!pq.empty() && pq.top().priority >= priority) {
            pq.push(Task(id, priority, arrival, -1, duration));
        } else {
            if (!pq.empty()) {
                stop(const_cast<Task&>(pq.top()), curr);
            }
            pq.push(Task(id, priority, arrival, curr, duration));
        }
    }
    while (!pq.empty()) {
        const Task &task = pq.top();
        curr = task.start + task.remain;
        printf("%d %d\n", task.id, curr);
        pq.pop();
        if (!pq.empty()) {
            start(const_cast<Task&>(pq.top()), curr);
        }
    }

    return 0;
}
