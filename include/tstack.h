// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kSize>
class TStack {
 private:
  T arr[kSize];
  int top;

 public:
  TStack() : top(-1) {}

  T get() const {
    return arr[top];
  }

  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == kSize - 1;
  }

  void pop() {
    if (top >= 0) {
      --top;
    }
  }

  void push(T item) {
    if (top < kSize - 1) {
      arr[++top] = item;
    }
  }
};

#endif  // INCLUDE_TSTACK_H_
