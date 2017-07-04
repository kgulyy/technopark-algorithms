/**
 * Дана последовательность целых чисел из диапазона (-10^9 .. 10^9). Длина последовательности не больше 10^6.
 * Числа записаны по одному в строке. Количество чисел не указано.
 * Пусть количество элементов n и числа записаны в массиве a = a[i]: i из [0..n-1].
 * Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
 * Указание : количество инверсий может быть больше 4*10^9 - используйте int64_t.
 */
#include <fstream>
#include <iostream>
#include "InversionCounter.h"
using namespace std;

/**
 * Чтение чисел в массив
 * @param vector
 */
void readNumbers(IntVector& vector);

int main() {
  // Чтение данных
  IntVector numbers;
  readNumbers(numbers);

  // Подсчет количества инверсий
  InversionCounter counter;
  long long result = counter.countInversion(numbers);

  // Печать результата
  cout << result;

  return 0;
}

void readNumbers(IntVector& vector) {
  ifstream in("input.txt");

  vector.clear();
  int number = 0;
  while(in >> number) {
    vector.push_back(number);
  }

  in.close();
}
