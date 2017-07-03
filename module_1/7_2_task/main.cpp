/**
 * 7_2. Заявки на переговоры.
 * В большой IT-фирме есть только одна переговорная комната.
 * Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
 * Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
 * Число заявок ​ ≤ 100000.
 * Формат входных данных: Вход содержит только пары целых чисел ​ — ​ начала и концы заявок.
 * Формат выходных данных: Выход должен содержать натуральное число ​ — максимальное число заявок.
 */
#include <fstream>
#include <iostream>
#include "Request.h"
using namespace std;

/**
 * Сортировка слиянием, итеративная реализация
 * @param array
 * @param size
 */
void mergeSortIterative(Request* array, size_t size);

/**
 * Процедура слияния для сортировки
 * @param array
 * @param left
 * @param mid
 * @param right
 */
void merge(Request* array, size_t left, size_t mid, size_t right);

/**
 * Вычисление максимального количества удовлетворенных заявок
 * @param requests массив заявок
 * @param size количество заявок
 * @return максимальное количество удовлетворенных заявок
 */
int calcMaxApprovedRequest(const Request* requests, size_t size);

int main() {
  // Выделение памяти и чтение заявок
  Request* requests = new Request[100000];
  size_t requestAmount = 0;
  int readNumber = 0;
  ifstream in("input.txt");
  while (in >> readNumber) {
    int start = readNumber;
    in >> readNumber;
    int finish = readNumber;
    requests[requestAmount++] = Request(start, finish);
  }
  in.close();

  // Сортировка заявок по времени окончания
  mergeSortIterative(requests, requestAmount);

  // Рассчет максимального количества, которое м.б удовлетворено
  int maxApprovedRequest = calcMaxApprovedRequest(requests, requestAmount);

  // Печать результата
  cout << maxApprovedRequest;

  // Очистка памяти
  delete[] requests;

  return 0;
}

void mergeSortIterative(Request* a, size_t size) {
  for (size_t i = 1; i < size; i *= 2) {
    for (size_t j = 0; j < size - 1; j += 2 * i) {
      size_t left = j;
      size_t mid = j + i;
      size_t right = min(j + 2 * i, size);
      if (mid < right) {
        merge(a, left, mid, right);
      }
    }
  }
}

void merge(Request* a, size_t left, size_t mid, size_t right) {
  size_t it1 = 0;
  size_t it2 = 0;
  Request* result = new Request[right - left];

  while (left + it1 < mid && mid + it2 < right) {
    if (a[left + it1].getFinish() <= a[mid + it2].getFinish()) {
      result[it1 + it2] = a[left + it1];
      it1++;
    } else {
      result[it1 + it2] = a[mid + it2];
      it2++;
    }
  }

  while (left + it1 < mid) {
    result[it1 + it2] = a[left + it1];
    it1++;
  }

  while (mid + it2 < right) {
    result[it1 + it2] = a[mid + it2];
    it2++;
  }

  for (int i = 0; i < it1 + it2; ++i) {
    a[left + i] = result[i];
  }

  delete[] result;
}

int calcMaxApprovedRequest(const Request* requests, size_t size) {
  int result = 1;
  size_t j = 0;
  for (size_t i = 1; i < size; ++i) {
    if (requests[i].getStart() >= requests[j].getFinish()) {
      result++;
      j = i;
    }
  }

  return result;
}
