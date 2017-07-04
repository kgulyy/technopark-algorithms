#include "StringSet.h"
#include <cstring>

StringSet::StringSet() {
  realSize = 0;
  table.resize(DEFAULT_CAPACITY);
  fill(table.begin(), table.end(), NIL);
}

bool StringSet::add(const string& value) {
  if (contains(value)) {
    return false;
  }

  if (1.0 * realSize / table.size() >= DEFAULT_LOAD_FACTOR)
    rehashTable();

  const int hash = hashCode(value);
  for (size_t i = 0; i < table.size(); ++i) {
    size_t index = getIndex(hash, i);

    if (isNilOrDeleted(table[index])) {
      table[index] = value;
      realSize++;
      return true;
    }
  }

  return false;
}

bool StringSet::remove(const string& value) {
  const int hash = hashCode(value);
  for (size_t i = 0; i < table.size(); ++i) {
    size_t index = getIndex(hash, i);

    if (isNil(table[index])) {
      return false;
    } else if (table[index] == value) {
      table[index] = DELETED;
      realSize--;
      return true;
    }
  }

  return false;
}

bool StringSet::contains(const string& value) const {
  const int hash = hashCode(value);
  for (size_t i = 0; i < table.size(); ++i) {
    size_t index = getIndex(hash, i);

    if (isNil(table[index]))
      return false;
    else if (table[index] == value) {
      return true;
    }
  }

  return false;
}

int StringSet::hashCode(const string& value) const {
  int hash = 0;
  if (value.length() > 0) {
    char val[value.length()];
    strcpy(val, value.c_str());

    for (int i = 0; i < value.length(); i++) {
      hash = 31 * hash + val[i];
    }
  }
  return hash;
}

bool StringSet::isNil(const string& value) const {
  return value == NIL;
}

bool StringSet::isNilOrDeleted(const string& value) const {
  return isNil(value) || value == DELETED;
}

size_t StringSet::getIndex(int hashCode, size_t i, size_t tableSize) const {
  const double FACTOR = 0.5;
  int hash = (int) (hashCode + FACTOR * i + FACTOR * i * i);
  return hash % tableSize;
}

size_t StringSet::getIndex(int hashCode, size_t i) const {
  return getIndex(hashCode, i, table.size());
}

void StringSet::rehashTable() {
  vector<string> newTable(table.size() * RESIZE_FACTOR);
  fill(newTable.begin(), newTable.end(), NIL);

  for (size_t i = 0; i < table.size(); ++i) {
    if (!isNilOrDeleted(table[i])) {
      const int hash = hashCode(table[i]);
      for (size_t j = 0; j < newTable.size(); ++j) {
        size_t index = getIndex(hash, j, newTable.size());
        if (isNil(newTable[index])) {
          newTable[index] = table[i];
          break;
        }
      }
    }
  }

  table = newTable;
}
