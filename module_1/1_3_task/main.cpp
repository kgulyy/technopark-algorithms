/**
 * ​1_3. Даны две рациональные дроби: a/b и c/d.
 * Сложить их и результат представьте в виде несократимой дроби n/m.
 * Вывести числа m и n.
 * a, b, c, d ≤ 1000.
 */

#include <fstream>
#include <iostream>
#include <assert.h>
using namespace std;

/**
 * Вычисление суммы дробей
 * @param a числитель 1й дроби
 * @param b знаменатель 1й дроби
 * @param c числитель 2й дроби
 * @param d знаменатель 2й дроби
 * @param n числитель результирующей дроби
 * @param m знаменатель результирующей дроби
 */
void calc(int a, int b, int c, int d, int& n, int& m);
// Вычисление НОК
int lcm(int first, int second);
// Вычисление НОД
int gcd(int first, int second);

int main() {
  int a, b, c, d, n, m = 0;

  ifstream in("input.txt");
  in >> a >> b >> c >> d;
  in.close();

  calc(a, b, c, d, n, m);

  cout << n << " " << m << endl;

  return 0;
}

void calc(int a, int b, int c, int d, int& n, int& m) {
  // вычисление общего знаменателя
  int denominator = lcm(b, d);

  assert(b);
  int firstMultiplier = denominator / b;

  assert(d);
  int secondMultiplier = denominator / d;

  int numerator = firstMultiplier * a + secondMultiplier * c;

  // вычисления НОД для числителя и знаменателя
  int divisor = gcd(numerator, denominator);

  assert(divisor);
  n = numerator / divisor;
  m = denominator / divisor;
}

int lcm(int first, int second) {
  int divisor = gcd(first, second);

  return divisor ? (first / divisor * second) : 0;
}

int gcd(int first, int second) {
  while (true) {
    if (first == 0) return second;
    second %= first;
    if (second == 0) return first;
    first %= second;
  }
}
