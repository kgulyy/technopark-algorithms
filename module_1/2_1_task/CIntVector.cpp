#include "CIntVector.h"
#include <assert.h>

CIntVector::CIntVector(size_t _size) : size(_size) {
  if (size == 0) {
    data = 0;
  } else {
    data = new int[size];
  }
}

CIntVector::~CIntVector() {
  delete[] data;
}

size_t CIntVector::Size() const {
  return size;
}

int CIntVector::operator[](int index) const {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}

int& CIntVector::operator[](int index) {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}
