#include "Stack.h"
#include <assert.h>

Stack::Stack(int size) {
  this->size = size;
  buffer = new char[size];
  top = -1;
}

Stack::~Stack() {
  delete[] buffer;
}

void Stack::push(char item) {
  assert(top + 1 < size);
  buffer[++top] = item;
}

char Stack::pop() {
  assert(top != -1);
  return buffer[top--];
}

bool Stack::isEmpty() {
  return top == -1;
}

char Stack::getTop() {
  assert(top != -1);
  return buffer[top];
}