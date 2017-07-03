#ifndef INC_4_3_TASK_QUEUE_H
#define INC_4_3_TASK_QUEUE_H

#include "Stack.h"

class Queue {
 private:
  Stack* inbox = new Stack(5);
  Stack* outbox = new Stack(5);

 public:
  virtual ~Queue();
  void push(int item);
  int pop();
};

#endif //INC_4_3_TASK_QUEUE_H
