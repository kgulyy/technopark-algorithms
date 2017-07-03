/**
 * 5_2. Стековые анаграммы.
 * Пара слов называется стековой анаграммой, если одно слово можно получить из другого,
 * проведя последовательность стековых операций с его буквами
 * (взять очередную букву исходного слова и поместить ее в стек;
 * взять букву из стека и добавить ее в конец выходного слова).
 * Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций,
 * переводящую первое слово во второе. Все буквы в слове различные.
 * Длина анаграммы ≤ 10000.
 * Формат входных данных. Пара слов, являющихся анаграммой.
 * Формат выходных данных. YES​ , если последовательность стековых операций существует и ​ NO​ в противном случае.
 */

#include <fstream>
#include <iostream>
#include "Stack.h"
using namespace std;

/**
 * Функция проверяет явлляется ли пара слов стековой аннаграммой
 * @param firstWord
 * @param secondWord
 * @return результат проверки
 */
bool isStackAnagram(const string& firstWord, const string& secondWord);

int main() {
  // Чтение входных данных
  ifstream in("input.txt");
  string firstWord;
  in >> firstWord;

  string secondWord;
  in >> secondWord;
  in.close();

  // Проверка пары слов на стековые аннаграммы
  bool result = isStackAnagram(firstWord, secondWord);

  // Печать результата
  result ? cout << "YES" : cout << "NO";

  return 0;
}

bool isStackAnagram(const string& firstWord, const string& secondWord) {
  int wordSize = (int) firstWord.size();
  Stack* stack = new Stack(wordSize);

  int i = 0;
  // Перебор букв 2го слова
  for (int j = 0; j < wordSize; ++j) {
    if (stack->isEmpty()) {
      // Вставка в стек поочереди букв 1го слова, пока не встретится буква равная текущей 2го слова
      do {
        stack->push(firstWord[i++]);
      } while (firstWord[i-1] != secondWord[j] && i < wordSize);
    }
    // Если вершина стека равна текущей букве 2го слова, то извлекаем ее из стека
    if (stack->getTop() == secondWord[j]) {
      stack->pop();
    }
  }

  // Если стек пуст - последовательность стековых операций существует
  bool result = stack->isEmpty();

  delete stack;

  return result;
}