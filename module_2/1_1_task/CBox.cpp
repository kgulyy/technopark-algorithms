#include "CBox.h"

bool CBox::operator<(const CBox& box) const {
  return Length * Length + Width * Width + High * High
      < box.Length * box.Length + box.Width * box.Width + box.High * box.High;
}