#include "Queue.h"

Queue::~Queue() {
  delete inbox;
  delete outbox;
}

void Queue::push(int item) {
  inbox->push(item);
}

int Queue::pop() {
  if (outbox->isEmpty()) {
    while (!inbox->isEmpty()) {
      outbox->push(inbox->pop());
    }
  }
  return outbox->pop();
}
