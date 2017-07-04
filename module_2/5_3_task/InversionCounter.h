#ifndef TASKS_INVERSIONCOUNTER_H
#define TASKS_INVERSIONCOUNTER_H

#include <vector>
using namespace std;

typedef vector<int> IntVector;

/**
 * Класс для подсчета количества инверсий в целочисленном массиве.
 * Алгоритм основан на сортировке слиянием
 */
class InversionCounter {
 private:
  IntVector vector;
  long long inversionCount;

 public:
  InversionCounter();
  long long countInversion(const IntVector& vector);

 private:
  void sortAndCountInversion();
  void mergeAndCountInversion(size_t left, size_t mid, size_t right);
};

#endif //TASKS_INVERSIONCOUNTER_H
