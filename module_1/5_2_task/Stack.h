#ifndef TASKS_STACK_H
#define TASKS_STACK_H

class Stack {
 private:
  char* buffer;
  int size;
  int top;

 public:
  Stack(int size);
  virtual ~Stack();
  void push(char item);
  char pop();
  bool isEmpty();
  char getTop();
};

#endif //TASKS_STACK_H