#ifndef TASKS_LINESEGMENT_H
#define TASKS_LINESEGMENT_H

struct LineSegment {
 private:
  int left;
  int right;

 public:
  LineSegment(int left, int right) : left(left), right(right) {}

  int getLeft() const {
    return left;
  }

  int getRight() const {
    return right;
  }

  int length() const {
    return right - left;
  }

  // Сравнение отрезков по левому краю, затем по правому
  bool operator<(const LineSegment& rhs) const {
    if (left < rhs.left)
      return true;
    if (rhs.left < left)
      return false;
    return right < rhs.right;
  }
  bool operator>(const LineSegment& rhs) const {
    return rhs < *this;
  }
  bool operator<=(const LineSegment& rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const LineSegment& rhs) const {
    return !(*this < rhs);
  }
};

#endif //TASKS_LINESEGMENT_H
