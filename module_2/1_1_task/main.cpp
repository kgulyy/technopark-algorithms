/**
 * 1_1. Ящики.
 * На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
 * Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается
 * в предыдущий). Один ящик можно вложить в другой, если его можно перевернуть так, что размеры
 * одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим
 * осям. Требуется определить, в какой последовательности они будут вложены друг в друга.
 * Вывести номера ящиков.
 */
#include <fstream>
#include <iostream>
#include <vector>
#include "CBox.h"
using namespace std;

/**
 * Сортировка вставками
 * @tparam T
 * @param arr
 * @param comparator
 */
template<class T>
void InsertionSort(vector<T>& arr, bool( * comparator )(const T&, const T&));

/**
 * Сравнитель коробок
 * @param first
 * @param second
 * @return результат сравнения
 */
bool BoxComparator(const CBox& first, const CBox& second);

int main() {
  ifstream in("input.txt");
  // Считывание количества коробок
  size_t amountBoxes = 0;
  in >> amountBoxes;

  // Считывание размеров коробок
  size_t length = 0;
  size_t width = 0;
  size_t high = 0;
  vector<CBox> boxes(amountBoxes);
  for (size_t i = 0; i < amountBoxes; ++i) {
    in >> length >> width >> high;
    boxes[i] = CBox(i, length, width, high);
  }
  in.close();

  // Сортировка коробок, путем сравнения их по диагоналям
  InsertionSort(boxes, BoxComparator);

  // Вывод результата
  for (const CBox& box : boxes) {
    cout << box.Id << " ";
  }

  return 0;
}

bool BoxComparator(const CBox& first, const CBox& second) {
  return first < second;
}

template<class T>
void InsertionSort(vector<T>& arr, bool( * comparator )(const T&, const T&)) {
  for (int j = 1; j < arr.size(); ++j) {
    int i = j - 1;
    while (i >= 0 && comparator(arr[i + 1], arr[i])) {
      swap(arr[i], arr[i + 1]);
      i--;
    }
  }
}
