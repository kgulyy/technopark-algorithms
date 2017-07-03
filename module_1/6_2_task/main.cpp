/**
 * Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
 * Формат входных данных: На вход подается количество кубиков N.
 * Формат выходных данных: Вывести число различных пирамид из N кубиков.
 *
 * 6_2. Широкая пирамида.​ Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
 * N ≤ 300.
 */
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Подсчет количества широких пирамид, которые можно построить из N кубиков
 * @param table таблица для рекурентных вычислений
 * @param n количество кубиков
 * @return количество пирамид
 */
long calcNumberPyramids(long** table, size_t n);

/**
 * Рекурентная функция подсчета количества пирамид с основанием basePyramid, которые можно посторить из numberCubes кубиков
 * @param table таблица для рекурентных вычислений
 * @param numberCubes количесво кубиков
 * @param basePyramid основание пирамиды
 * @return результат рекуретной функции
 */
long recurrentFunction(long** table, size_t numberCubes, size_t basePyramid);

int main() {
  // Чтение входных данных
  ifstream in("input.txt");
  size_t n = 0;
  in >> n;
  in.close();

  // Выделение памяти под таблицу для рекурентных вычислений
  const size_t sizeTable = n + 1;
  long** table = new long* [sizeTable];
  for (size_t i = 0; i < sizeTable; ++i) {
    table[i] = new long[sizeTable];
  }

  // Вычисление количества пирамид
  long numberPyramids = calcNumberPyramids(table, n);

  // Печать результата
  cout << numberPyramids;

  // Освобождение памяти
  for (int i = 0; i < sizeTable; ++i) {
    delete[] table[i];
  }
  delete[] table;
}

long calcNumberPyramids(long** table, size_t n) {
  size_t sizeTable = n + 1;

  // Инициализация нулевой строки
  for (size_t j = 0; j < sizeTable; ++j) {
    table[0][j] = 1;
  }

  // Инициализация нулевого столбеца
  for (size_t i = 1; i < sizeTable; ++i) {
    table[i][0] = 0;
  }

  // Инициализация треугольной матрицы
  for (size_t i = 1; i < sizeTable - 2; ++i) {
    for (size_t j = 1; j < sizeTable - i - 1; ++j) {
      table[i][j] = recurrentFunction(table, i, j);
    }
  }

  // Инициализация последней строки
  for (size_t j = 1; j < sizeTable; ++j) {
    table[n][j] = recurrentFunction(table, n, j);
  }

  return recurrentFunction(table, n, n);
}

long recurrentFunction(long** table, size_t numberCubes, size_t basePyramid) {
  int difference = (int) (numberCubes - basePyramid);
  long firstTerm = 0;
  if (difference >= 0) {
    firstTerm = table[difference][basePyramid - 1];
  }
  long secondTerm = table[numberCubes][basePyramid - 1];

  return firstTerm + secondTerm;
}
