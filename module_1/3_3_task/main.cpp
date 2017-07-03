/**
 * ​3_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. a[0..n-1] и b[0..m-1]. n >> m.
 * Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта b[m-1] в массиве a.
 * В процессе поиска очередного элемента b[i] в массиве a пользуйтесь результатом поиска элемента b[i-1].
 * n, k ≤ 10000.
 */

#include <fstream>
#include <iostream>
using namespace std;

/**
 * Поиск пересечения двух массивов
 * @in a 1ый массив
 * @in n размер 1го массива
 * @in b 2ой массив
 * @in m размер 2го массива
 * @out result результирующий массив
 * @out resultSize размер результирующего массива
 */
void findIntersection(int* a, int n, int* b, int m, int* result, int& resultSize);

/**
 * Рекурсивная функция бинарного поиска элемента в массиве
 * @param array исходный массив
 * @param value искомое значение
 * @param low нижния граница поиска
 * @param high верхняя граница поиска
 * @return результат поиска
 */
int binarySearch(int* array, int value, int low, int high);

int main() {
  // Считывание входных данных
  ifstream in("input.txt");
  int n = 0;
  in >> n;

  int m = 0;
  in >> m;

  int* a = new int[n];
  for (int i = 0; i < n; ++i) {
    in >> a[i];
  }

  int* b = new int[m];
  for (int i = 0; i < m; ++i) {
    in >> b[i];
  }
  in.close();

  // Иницилизация результирующего массива
  int* result = new int[m];
  for (int i = 0; i < m; ++i) {
    result[i] = 0;
  }

  // Нахождение пересечения
  int resultSize = 0;
  findIntersection(a, n, b, m, result, resultSize);

  // Вывод результата
  for (int i = 0; i < resultSize; ++i) {
    cout << result[i] << " ";
  }

  // Очистка памяти
  delete[] a;
  delete[] b;
  delete[] result;
}

void findIntersection(int* a, int n, int* b, int m, int* result, int& resultSize) {
  // Поиск производиться по степеням двойки начиная с нулевой
  int startSearchIndex = 1;

  // Поиск всех элементов из 2го массива в 1ом
  for (int j = 0; j < m; ++j) {
    // 1ый массив перебирается по степеням двойки
    for (int i = startSearchIndex; i < n; i *= 2) {
      // Если элементы равны, то записываем в результирующий массив
      if (b[j] == a[i]) {
        result[resultSize++] = a[i];
        startSearchIndex = i;
        break;
      } else if (b[j] < a[i]) {
        // Проверка нулевого элемента
        if (a[0] == b[j]) {
          result[resultSize++] = a[0];
        }
        break;
      } else if (b[j] > a[i]) {
        // Бинарный поиск по оставшимся элементам до верхней границы
        int high = i * 2 - 1;
        if (high > n)
          high = n;
        int resultIndex = binarySearch(a, b[j], i + 1, high);
        if (resultIndex >= 0)
          result[resultSize++] = a[resultIndex];
      }
    }
  }
}

int binarySearch(int* array, int value, int low, int high) {
  if (high < low) {
    return -1;
  }

  if (high == low) {
    if (array[low] == value)
      return low;
    else
      return -1;
  }

  int mid = (low + high) / 2;
  if (array[mid] == value) {
    return mid;
  }

  if (array[mid] > value) {
    return binarySearch(array, value, low, mid - 1);
  } else {
    return binarySearch(array, value, mid + 1, high);
  }
}
