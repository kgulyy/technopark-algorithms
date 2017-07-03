/**
 * Во всех задачах из следующего списка следует написать структуру данных,
 * обрабатывающую команды push и pop.
 *
 * Формат входных данных:
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Для очереди используются команды 2 и 3.
 * Если дана команда pop, то число b - ожидаемое значение.
 * Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Формат выходных данных.
 * Требуется напечатать YES - если все ожидаемые значения совпали.
 * Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * 4_3. ​Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 */

#include "Queue.h"
#include <fstream>
#include <iostream>
using namespace std;

enum Command {
  POP_FRONT = 2,
  PUSH_BACK = 3
};

/**
 * Функция моделирующая операции вставки и извлечения из очереди
 * И проверяющая правильность результата
 * @param cmd таблица команда
 * @param numberCmd количесво команд
 * @return правильность результата
 */
bool queueModelingAndCheck(int** cmd, size_t numberCmd);

int main() {
  // Чтение входных данных
  ifstream in("input.txt");
  size_t numberCmd = 0;
  in >> numberCmd;

  // Иницилизация таблицы команд
  int** commands = new int* [numberCmd];
  for (int i = 0; i < numberCmd; ++i) {
    commands[i] = new int[2];
    commands[i][0] = 0;
    commands[i][1] = 0;
  }

  // Заполнение таблицы команд
  for (int i = 0; i < numberCmd; ++i) {
    in >> commands[i][0];
    in >> commands[i][1];
  }
  in.close();

  // Моделирование очереди и проверка
  bool result = queueModelingAndCheck(commands, numberCmd);

  // Печать результата
  result ? cout << "YES\n" : cout << "NO\n";

  // Очистка памяти
  for (int i = 0; i < numberCmd; ++i) {
    delete[] commands[i];
  }
  delete[] commands;

  return 0;
}

bool queueModelingAndCheck(int** cmd, size_t numberCmd) {
  Queue queue;
  for (int i = 0; i < numberCmd; ++i) {
    Command command = (Command) cmd[i][0];
    int number = cmd[i][1];

    switch (command) {
      case PUSH_BACK:
        queue.push(number);
        break;
      case POP_FRONT:
        int expectedNumber = number;
        int actualNumber = queue.pop();
        if (expectedNumber != actualNumber)
          return false;
    }
  }
  return true;
}