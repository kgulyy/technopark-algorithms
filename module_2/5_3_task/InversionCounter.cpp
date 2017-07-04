#include "InversionCounter.h"

InversionCounter::InversionCounter() {
  inversionCount = 0;
}

void InversionCounter::sortAndCountInversion() {
  size_t size = vector.size();
  for (size_t i = 1; i < size; i *= 2) {
    for (size_t j = 0; j < size - 1; j += 2 * i) {
      size_t left = j;
      size_t mid = j + i;
      size_t right = min(j + 2 * i, size);
      if (mid < right) {
        mergeAndCountInversion(left, mid, right);
      }
    }
  }
}

void InversionCounter::mergeAndCountInversion(size_t left, size_t mid, size_t right) {
  size_t iter_1 = 0;
  size_t iter_2 = 0;
  IntVector result(right - left);

  while (left + iter_1 < mid && mid + iter_2 < right) {
    if (vector[left + iter_1] <= vector[mid + iter_2]) {
      result[iter_1 + iter_2] = vector[left + iter_1];
      iter_1++;
    } else {
      result[iter_1 + iter_2] = vector[mid + iter_2];
      iter_2++;

      size_t restCount = mid - left - iter_1;
      inversionCount += restCount;
    }
  }

  while (left + iter_1 < mid) {
    result[iter_1 + iter_2] = vector[left + iter_1];
    iter_1++;
  }

  while (mid + iter_2 < right) {
    result[iter_1 + iter_2] = vector[mid + iter_2];
    iter_2++;
  }

  for (int i = 0; i < iter_1 + iter_2; ++i) {
    vector[left + i] = result[i];
  }
}

long long InversionCounter::countInversion(const IntVector& vector) {
  inversionCount = 0;
  this->vector = vector;
  sortAndCountInversion();
  return inversionCount;
}