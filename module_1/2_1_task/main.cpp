/**
 * 2_1. Даны два массива целых чисел одинаковой длины a[0..n-1] и b[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0,
 * такую что a[i0] + b[j0] = max {a[i] + b[j], где 0 <= i < n, 0 <= j < n, i <= j}.
 * Время работы - O(n).
 */

#include "CIntVector.h"
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Заполение вектора данными из входного потока
 * @param vector исходный массив
 * @param in входной поток данных
 */
void fillVector(CIntVector& vector, istream& in);

/**
 * Поиск первой пары индексов исходных массивов, удовлетворяющие условиям задачи
 * @in a первый массив
 * @in b второй массив
 * @in n размер массивов a и b
 * @out resIndexA результирующий индекс массива a
 * @out resIndexB результирующий индекс массива b
 */
void findIndexes(const CIntVector& a, const CIntVector& b, size_t n, size_t& resIndexA, size_t& resIndexB) ;

int main() {
  // Чтение входных данных
  ifstream in("input.txt");
  size_t n = 0;
  in >> n;

  CIntVector a(n);
  fillVector(a, in);

  CIntVector b(n);
  fillVector(b, in);
  in.close();

  // Решение задачи
  size_t resIndexA = 0;
  size_t resIndexB = 0;
  findIndexes(a, b, n, resIndexA, resIndexB);

  // Вывод результата
  cout << resIndexA << " " << resIndexB;

  return 0;
}

void fillVector(CIntVector& vector, istream& in) {
  for (size_t i = 0; i < vector.Size(); ++i) {
    in >> vector[i];
  }
}

void findIndexes(const CIntVector& a, const CIntVector& b, size_t n, size_t& resIndexA, size_t& resIndexB) {
  resIndexA, resIndexB = 0;
  size_t maxIndexA = 0;

  for (size_t i = 1; i < n; ++i) {
    // Находение текущего максимума массива a
    if (a[i] > a[maxIndexA]) {
      maxIndexA = i;
    }
    // Проверка наличия новой пары с максимальной суммой
    if (a[maxIndexA] + b[i] > a[resIndexA] + b[resIndexB]) {
      resIndexA = maxIndexA;
      resIndexB = i;
    }
  }
}
