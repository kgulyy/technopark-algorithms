#ifndef TASKS_MAXHEAP_H
#define TASKS_MAXHEAP_H

#include <vector>
#include "LineSegment.h"
using namespace std;

typedef vector<LineSegment> SegmentVector;

class MaxHeap {
 private:
  SegmentVector& vector;
  size_t size;

 public:
  MaxHeap(SegmentVector& vector);

  // Размер кучи
  size_t Size();

  // Построение кучи
  void Build();

  // Проталкивание элемента вниз
  void SiftDown(size_t index);

  // Перемещение верхнего элемента в конец, изменение размера и восстановление кучи
  void MoveTopToBackResizeAndRestoreHeap();
};

#endif //TASKS_MAXHEAP_H
