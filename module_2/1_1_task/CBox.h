#ifndef TASKS_CBOX_H
#define TASKS_CBOX_H

#include "stdlib.h"
using namespace std;

struct CBox {
  size_t Id;
  size_t Length;
  size_t Width;
  size_t High;

  CBox() : Id(0), Length(0), Width(0), High(0) {}
  CBox(size_t id, size_t length, size_t width, size_t high) : Id(id), Length(length), Width(width), High(high) {}

  // Сравнение квадрата диагоналей параллелепипедов (коробок)
  bool operator<(const CBox& box) const;
};

#endif //TASKS_CBOX_H
