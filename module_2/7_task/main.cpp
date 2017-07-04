/**
 * Дан массив целых чисел в диапазоне [0..10^9].
 * Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов.
 * Все значения массива являются элементами псевдо-рандомной последовательности.
 * Необходимо отсортировать элементы массива за минимальное время
 * и вывести каждый 10-й элемент отсортированной последовательности.
 * Реализуйте сортировку, основанную на QuickSort.
 * Минимальный набор оптимизаций, который необходимо реализовать:
 * 1. Оптимизация ввода/вывода
 * 2. Оптимизация выбора опорного элемента
 * 3. Оптимизация Partition
 * 4. Оптимизация рекурсии
 * 5. Оптимизация концевой рекурсии
 *
 * Лучший результат 5.991s / 190.92Mb
 */
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

void quickSort(size_t* a, size_t size);
void insertionSort(size_t* a, size_t left, size_t right);
size_t partition(size_t* a, size_t left, size_t right);
size_t selectPivotIndex(size_t* a, size_t first, size_t last);

typedef pair<size_t, size_t> Command;

int main() {
  const size_t CAPACITY_OF_ARRAY = 25000000;
  size_t* a = new size_t[CAPACITY_OF_ARRAY];

  size_t size = 0;
  size_t number = 0;
  ifstream cin("input.txt");
  while (cin >> number) {
    a[size++] = number;
  }
  cin.close();

  quickSort(a, size);

  for (int i = 9; i < size; i += 10) {
    cout << a[i] << " ";
  }

  delete[] a;

  return 0;
}

void quickSort(size_t* a, size_t size) {
  stack<Command> commands;
  size_t start = 0;
  size_t end = size - 1;
  commands.push(make_pair(start, end));

  size_t level = 15;

  while (!commands.empty()) {
    Command cmd = (pair<size_t, size_t>&&) commands.top();
    commands.pop();

    size_t boundary = partition(a, cmd.first, cmd.second);
    size_t leftPartSize = boundary - cmd.first;
    size_t rightPartSize = cmd.second - boundary + 1;

    if (leftPartSize > rightPartSize) {
      if (leftPartSize > 1) {
        if (leftPartSize <= level)
          insertionSort(a, cmd.first, boundary - 1);
        else
          commands.push(make_pair(cmd.first, boundary - 1));
      }

      if (rightPartSize > 1) {
        if (rightPartSize <= level)
          insertionSort(a, boundary + 1, cmd.second);
        else
          commands.push(make_pair(boundary + 1, cmd.second));
      }
    } else {
      if (rightPartSize > 1) {
        if (rightPartSize <= level)
          insertionSort(a, boundary + 1, cmd.second);
        else
          commands.push(make_pair(boundary + 1, cmd.second));
      }

      if (leftPartSize > 1) {
        if (leftPartSize <= level)
          insertionSort(a, cmd.first, boundary - 1);
        else
          commands.push(make_pair(cmd.first, boundary - 1));
      }
    }
  }
}

void insertionSort(size_t* a, size_t left, size_t right) {
  for (size_t j = left + 1; j <= right; ++j) {
    int i = (int) (j - 1);
    while (i >= 0 && a[i + 1] < a[i]) {
      swap(a[i], a[i + 1]);
      i--;
    }
  }
}

size_t partition(size_t* a, size_t left, size_t right) {
  // выбираем опорный элемент
  size_t pivotIndex = selectPivotIndex(a, left, right);
  size_t pivot = a[pivotIndex];
  // меняем опорный и последний элементы
  swap(a[pivotIndex], a[right]);

  // итератор изначально указывает на первый элемент
  size_t i = left;
  // двигаем итератор до элемента, который больше опорного
  while (i < right && a[i] <= pivot) {
    i++;
  }
  // второй итератор указывает на тот же элемент
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

  // меняем опорный и i-й элементы
  swap(a[i], a[right]);

  return i;
}

size_t selectPivotIndex(size_t* a, size_t first, size_t last) {
  // выбираем серединный элемент
  size_t mid = (first + last) / 2;

  // выбираем медиану из первого, последнего и серединного элементов
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