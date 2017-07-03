#include "Stack.h"
#include <assert.h>
#include <cstring>

Stack::Stack(int size) {
  this->size = size;
  buffer = new int[size];
  top = -1;
}

Stack::~Stack() {
  delete[] buffer;
}

void Stack::push(int item) {
  if (top == size - 1) {
    // Увеличение памяти стека в 2х кратном размере
    const int BUFFER_MULTIPLIER = 2;
    int* newBuffer = new int[size * BUFFER_MULTIPLIER];
    memcpy(newBuffer, buffer, sizeof(int) * size);
    delete[] buffer;
    buffer = newBuffer;
    buffer[++top] = item;
    size *= BUFFER_MULTIPLIER;
  } else {
    buffer[++top] = item;
  }
}

int Stack::pop() {
  assert(top != -1);
  return buffer[top--];
}

bool Stack::isEmpty() {
  return top == -1;
}
