#ifndef INC_2_1_TASK_CINTVECTOR_H
#define INC_2_1_TASK_CINTVECTOR_H

#include <istream>
using namespace std;

class CIntVector {
 public:
  CIntVector(size_t size);
  ~CIntVector();

  size_t Size() const;

  // Операторы доступа к элементам по индексу.
  // Константный оператор возвращает копию элемента.
  int operator[](int index) const;
  // Неконстантный оператор возвращает ссылку на элемент.
  int& operator[](int index);

 private:
  int* data;
  size_t size;
};

#endif