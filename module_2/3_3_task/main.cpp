/**
 * 3_3. Закраска прямой 1.
 * На числовой прямой окрасили ​N ​отрезков.
 * Известны координаты левого и правого концов каждого отрезка (L​i​ и R​i).
 * Найти длину окрашенной части числовой прямой.
 */

#include <fstream>
#include <iostream>
#include "LineSegment.h"
#include "MaxHeap.h"
using namespace std;

/**
 * Расчет длины закрашенной прямой
 * @param vector сегменты прямой
 * @return длина закрашенной части
 */
int calcPaintedLength(SegmentVector& vector);

/**
 * Процедура пирамидальной сортировки
 * @param vector
 */
void heapSort(SegmentVector& vector);

int main() {
  // Чтение данных
  ifstream in("input.txt");
  size_t n = 0;
  in >> n;

  SegmentVector vector;
  for (size_t i = 0; i < n; ++i) {
    int left = 0;
    int right = 0;
    in >> left;
    in >> right;
    vector.push_back(LineSegment(left, right));
  }
  in.close();

  // Расчет длины закрашенной части
  int paintedLength = calcPaintedLength(vector);

  // Печать результата
  cout << paintedLength;

  return 0;
}

int calcPaintedLength(SegmentVector& vector) {
  // Сортировка отрезков по левому краю
  heapSort(vector);
  // Запись длины 1го отрезка в результат
  int result = vector[0].length();
  // Индекс вектора с текущей максимальной правой границей
  int indexMaxRight = 0;
  // Перебор остальных отрезков
  for (int i = 1; i < vector.size(); ++i) {
    // Сравнение левого края текущего с максимальной правой границей
    if (vector[i].getLeft() >= vector[indexMaxRight].getRight()) {
      // Добавление длины текущего отрезка к результату
      result += vector[i].length();
      // Изменение максимальной правой границы
      indexMaxRight = i;
    } else {
      int dif = vector[i].getRight() - vector[indexMaxRight].getRight();
      if (dif > 0) {
        // Добавление положительной разницы к результату
        result += dif;
        // Изменение максимальной правой границы
        indexMaxRight = i;
      }
    }
  }

  return result;
}

void heapSort(SegmentVector& vector) {
  MaxHeap heap = MaxHeap(vector);
  while (heap.Size() > 1) {
    heap.MoveTopToBackResizeAndRestoreHeap();
  }
}
