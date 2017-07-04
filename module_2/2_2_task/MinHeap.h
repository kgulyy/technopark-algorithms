#ifndef TASKS_MINHEAP_H
#define TASKS_MINHEAP_H

#include <vector>
using namespace std;

typedef vector<int> IntVector;

class MinHeap {
 private:
  IntVector vector;

 public:
  MinHeap(const IntVector& vector);
  // Размер кучи
  size_t Size();
  // Построение кучи
  void Build();
  // Проталкивание элемента вниз
  void SiftDown(long long index);
  // Проталкивание элемента наверх
  void SiftUp(long long index);
  // Добавление элемента
  void Add(int number);
  // Извлечение верхнего элемента
  int ExtractTop();
};

#endif //TASKS_MINHEAP_H
