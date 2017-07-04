/**
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику.
 * Т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 *
 * 4_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Поиск k-й порядковой статистики
 * @param array массив элементов
 * @param n размер массива
 * @param k порядковый номер искомого элемента
 * @return искомый элемент
 */
int findOrderStatistic(int* array, size_t n, size_t k);

/**
 * Разбиение массива на 2 подмассива
 * @param a массив элементов
 * @param left индекс начала области
 * @param right индекс конца области
 * @return индекс опорного элемента
 */
size_t partition(int* a, size_t left, size_t right);

/**
 * Выбор опорного элемента
 * @param a массив элементов
 * @param first индекс начала области
 * @param last индекс конца области
 * @return опорный элемент
 */
size_t selectPivotIndex(int* a, size_t first, size_t last);

int main() {
  // Чтение данных
  ifstream in("input.txt");
  size_t n = 0;
  size_t k = 0;
  in >> n;
  in >> k;

  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    in >> array[i];
  }
  in.close();

  // Нахождение k-й порядковой статистики
  int result = findOrderStatistic(array, n, k);

  // Печать результата
  cout << result;

  // Освобождение памяти
  delete[] array;

  return 0;
}

int findOrderStatistic(int* array, size_t n, size_t k) {
  size_t left = 0;
  size_t right = n - 1;
  while (true) {
    size_t mid = partition(array, left, right);
    if (mid == k) {
      return array[mid];
    } else if (k < mid) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
}

size_t partition(int* a, size_t left, size_t right) {
  // Выбор опорного элемента
  size_t pivotIndex = selectPivotIndex(a, left, right);
  int pivot = a[pivotIndex];
  // Меняем опорный и последний элементы
  swap(a[pivotIndex], a[right]);

  // Итератор изначально указывает на первый элемент
  size_t i = left;
  // Двигаем итератор до элемента, который больше опорного
  while (i < right && a[i] <= pivot) {
    i++;
  }
  // Второй итератор указывает на тот же элемент
  size_t j = i;

  while (j < right) {
    if (a[j] > pivot)
      j++;
    else {
      swap(a[i], a[j]);
      i++;
      j++;
    }
  }

  // Меняем опорный и i-й элементы
  swap(a[i], a[right]);

  return i;
}

size_t selectPivotIndex(int* a, size_t first, size_t last) {
  // Выбираем серединный элемент
  size_t mid = (first + last) / 2;

  // Выбираем медиану из первого, последнего и серединного элементов
  if (a[first] <= a[mid]) {
    if (a[mid] <= a[last]) {
      return mid;
    } else {
      if (a[first] <= a[last])
        return last;
      else
        return first;
    }
  } else {
    if (a[mid] <= a[last]) {
      if (a[first] <= a[last])
        return first;
      else
        return last;
    } else {
      return mid;
    }
  }
}
