#ifndef TASKS_STRINGSET_H
#define TASKS_STRINGSET_H

#include <string>
#include <vector>
using namespace std;

class StringSet {
 private:
  const size_t DEFAULT_CAPACITY = 8;
  const double DEFAULT_LOAD_FACTOR = 0.75;
  const size_t RESIZE_FACTOR = 2;
  const string NIL = "$_NIL_$";
  const string DELETED = "$_DELETED_$";

  vector<string> table;
  size_t realSize;

 public:
  StringSet();
  bool add(const string& value);
  bool remove(const string& value);
  bool contains(const string& value) const;

 private:
  int hashCode(const string& value) const;
  size_t getIndex(int hashCode, size_t i, size_t tableSize) const;
  size_t getIndex(int hashCode, size_t i) const;
  bool isNil(const string& value) const;
  bool isNilOrDeleted(const string& value) const;
  void rehashTable();
};

#endif //TASKS_STRINGSET_H
