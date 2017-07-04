#include "MaxHeap.h"

MaxHeap::MaxHeap(SegmentVector& vector) : vector(vector) {
  size = vector.size();
  Build();
}

size_t MaxHeap::Size() {
  return size;
}

void MaxHeap::Build() {
  for (int i = (int) (size / 2 - 1); i >= 0; --i) {
    SiftDown((size_t) i);
  }
}

void MaxHeap::SiftDown(size_t index) {
  size_t left = 2 * index + 1;
  size_t right = 2 * index + 2;

  size_t least = index;
  if (left < size && vector[left] > vector[least])
    least = left;
  if (right < size && vector[right] > vector[least])
    least = right;

  if (least != index) {
    iter_swap(vector.begin() + index, vector.begin() + least);
    SiftDown(least);
  }
}

void MaxHeap::MoveTopToBackResizeAndRestoreHeap() {
  iter_swap(vector.begin(), vector.begin() + size - 1);
  --size;
  SiftDown(0);
}
