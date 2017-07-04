/**
 * 2_2. Быстрое сложение.
 * Для сложения чисел используется старый компьютер.
 * Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
 * Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
 * в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9
 * ((1+3)+2) -> 1+3 + 4+2 = 10
 * ((2+3)+1) -> 2+3 + 5+1 = 11
 * Требуется написать программу, которая определяет минимальное время, достаточное для
 * вычисления суммы заданного набора чисел.
 * Формат входных данных.​ Вначале вводится n - количество чисел.
 * Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9,
 * сумма всех чисел не превосходит 2*10^9).
 * Формат выходных данных.​ Натуральное число - минимальное время.
 */
#include <fstream>
#include <iostream>
#include "MinHeap.h"
using namespace std;

/**
 * Подсчет минимального веремени, которое необходимо затратить, чтобы сложить набор чисел на "старом" компьютере
 * @param vector набор чисел
 * @return время
 */
int calcMinAdditionTime(const IntVector& vector);

int main() {
  // Чтение данных
  ifstream in("input.txt");
  size_t size = 0;
  in >> size;

  IntVector vector(size);
  for (int i = 0; i < size; ++i) {
    in >> vector[i];
  }
  in.close();

  // Подсчет вермени, затраченного на сложение набора чисел
  int result = calcMinAdditionTime(vector);

  // Печать результата
  cout << result;

  return 0;
}

int calcMinAdditionTime(const IntVector& vector) {
  MinHeap heap(vector);
  int result = 0;

  while (heap.Size() > 1) {
    int first = heap.ExtractTop();
    int second = heap.ExtractTop();
    int sum = first + second;
    result += sum;
    heap.Add(sum);
  }

  return result ? result : heap.ExtractTop();
}
