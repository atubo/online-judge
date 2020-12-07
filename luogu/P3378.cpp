// https://www.luogu.com.cn/problem/P3378
// 【模板】堆

#include <bits/stdc++.h>
using namespace std;

class Heap {
  int sz_;
  int *val_;
  int cap_;

  void alloc() {
    val_ = new int[cap_]{};
  }

  void dealloc() {
    delete[] val_;
  }

  void bubbleUp() {
    int u = sz_;
    while (u > 1 && val_[u] < val_[u/2]) {
      swap(val_[u], val_[u/2]);
      u = u / 2;
    }
  }

  void bubbleDown() {
    int u = 1;
    while (true) {
      if (2*u > sz_) break;
      if (2*u+1 > sz_) {
        if (val_[u] > val_[2*u]) {
          swap(val_[u], val_[2*u]);
          u = u * 2;
        } else {
          break;
        }
      } else {
        int ch = val_[2*u] < val_[2*u+1] ? 2*u : 2*u+1;
        if (val_[u] > val_[ch]) {
          swap(val_[u], val_[ch]);
          u = ch;
        } else {
          break;
        }
      }
    }
  }

 public:
  Heap(int n) : sz_(0), cap_(n+1) {
    alloc();
  }

  ~Heap() {
    dealloc();
  }

  void push(int x) {
    val_[++sz_] = x;
    bubbleUp();
  }

  int top() const {
    return val_[1];
  }

  void pop() {
    swap(val_[1], val_[sz_--]);
    bubbleDown();
  }
};

int main() {
  int n;
  scanf("%d", &n);
  Heap heap(n);
  for (int i = 0; i < n; i++) {
    int op, x;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d", &x);
      heap.push(x);
    } else if (op == 2) {
      printf("%d\n", heap.top());
    } else {
      heap.pop();
    }
  }
  return 0;
}
