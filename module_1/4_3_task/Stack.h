#ifndef INC_4_3_TASK_STACK_H
#define INC_4_3_TASK_STACK_H

class Stack {
 private:
  int* buffer;
  int size;
  int top;

 public:
  Stack(int size);
  virtual ~Stack();
  void push(int item);
  int pop();
  bool isEmpty();
};

#endif //INC_4_3_TASK_STACK_H
