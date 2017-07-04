/**
 * 6_3. Binary MSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6.
 * Отсортировать массив методом MSD по битам (бинарный QuickSort).
 */
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

/**
 * Процедура бинарной быстрой сортировки
 * @param a массив данных
 * @param size размер массива
 */
void binaryQuickSort(int64_t* a, size_t size);

/**
 * Разделение массива на 2 подмассива
 * @param a массив данных
 * @param left индекс левой границы
 * @param right индекс правой границы
 * @param bitPosition позиция бита
 * @return индекс первого элемента с выставленным битом в позиции
 */
size_t partition(int64_t* a, size_t left, size_t right, size_t bitPosition);

/**
 * Функция проверки выставлен ли бит у числа в заданной позиции
 */
bool isBitSet(int64_t number, size_t position);

int main() {
  // Чтение данных
  ifstream in("input.txt");
  size_t size = 0;
  in >> size;

  int64_t* array = new int64_t[size];
  for (int i = 0; i < size; ++i) {
    in >> array[i];
  }
  in.close();

  // Сортировка MSD по битам
  binaryQuickSort(array, size);

  // Печать результата сортировки
  for (int i = 0; i < size; ++i) {
    cout << array[i] << " ";
  }

  // Освобождение памяти
  delete[] array;

  return 0;
}

struct Command {
  size_t left;
  size_t right;
  size_t bitPosition;

  Command(size_t left, size_t right, size_t bitPosition) : left(left), right(right), bitPosition(bitPosition) {}

  Command(const Command& cmd) {
    left = cmd.left;
    right = cmd.right;
    bitPosition = cmd.bitPosition;
  }
};

void binaryQuickSort(int64_t* a, size_t size) {
  const size_t BIT_IN_BYTE = 8;
  const size_t HIGH_ORDER_BIT = sizeof(int64_t) * BIT_IN_BYTE - 1;
  // Стек команд для сортировки подмассивов
  stack<Command> commands;
  // Начинаем сортировку со старшего бита
  commands.push(Command(0, size - 1, HIGH_ORDER_BIT));

  while (!commands.empty()) {
    // Берем команду из стека
    Command currentCmd = commands.top();
    commands.pop();
    // Делаем разделение
    size_t boundary = partition(a, currentCmd.left, currentCmd.right, currentCmd.bitPosition);
    // Считаем размер подмассивов
    size_t leftPartSize = boundary - currentCmd.left;
    size_t rightPartSize = currentCmd.right - boundary + 1;
    // Сначала добавляем в стек команду для обработки большего подмассива
    if (leftPartSize >= rightPartSize) {
      if (leftPartSize > 1)
        commands.push(Command(currentCmd.left, boundary - 1, currentCmd.bitPosition - 1));
      if (rightPartSize > 1)
        commands.push(Command(boundary, currentCmd.right, currentCmd.bitPosition - 1));
    } else {
      if (rightPartSize > 1)
        commands.push(Command(boundary, currentCmd.right, currentCmd.bitPosition - 1));
      if (leftPartSize > 1)
        commands.push(Command(currentCmd.left, boundary - 1, currentCmd.bitPosition - 1));
    }
  }
}

size_t partition(int64_t* a, size_t left, size_t right, size_t bitPosition) {
  size_t i = left;
  // Двигаем первый итератор до элемента, у которого выставлен бит в позиции
  while (i < right && !isBitSet(a[i], bitPosition)) ++i;
  size_t j = i;
  // Два итератора двигаются от начала в конец подмассива
  while (j <= right) {
    if (isBitSet(a[j], bitPosition))
      ++j;
    else {
      swap(a[i], a[j]);
      ++i;
      ++j;
    }
  }
  // Возвращаем индекс первого элемента с выставленным битом в позиции
  return i;
}

bool isBitSet(int64_t number, size_t position) {
  return (number >> position & 1) == 1;
}
