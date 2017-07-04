#include "MinHeap.h"
#include <assert.h>

MinHeap::MinHeap(const IntVector& vector) : vector(vector) {
  Build();
}

size_t MinHeap::Size() {
  return vector.size();
}

void MinHeap::Build() {
  for (long long i = vector.size() / 2 - 1; i >= 0; --i) {
    SiftDown(i);
  }
}

void MinHeap::SiftDown(long long index) {
  long long left = 2 * index + 1;
  long long right = 2 * index + 2;

  long long least = index;
  if (left < vector.size() && vector[left] < vector[least])
    least = left;
  if (right < vector.size() && vector[right] < vector[least])
    least = right;

  if (least != index) {
    iter_swap(vector.begin() + index, vector.begin() + least);
    SiftDown(least);
  }
}

void MinHeap::SiftUp(long long index) {
  while (index > 0) {
    long long parent = (index - 1) / 2;
    if (vector[index] >= vector[parent])
      return;
    iter_swap(vector.begin() + index, vector.begin() + parent);
    index = parent;
  }
}

void MinHeap::Add(int number) {
  vector.push_back(number);
  SiftUp(vector.size() - 1);
}

int MinHeap::ExtractTop() {
  assert(!vector.empty());
  // Запоминаем значение корня.
  int result = vector[0];
  // Переносим последний элемент в корень.
  vector[0] = vector.back();
  vector.pop_back();
  // Вызываем SiftDown для корня.
  if (!vector.empty()) {
    SiftDown(0);
  }
  return result;
}