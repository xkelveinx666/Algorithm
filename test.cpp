#include <iostream>
using namespace std;
int main(void) {
  int a, b, c, d;
  int sum = 711;
  for (a = 0; a <= sum; a++) {
    for (b = 0; b <= sum - a; b++) {
      for (c = 0; c <= sum - a - b; c++) {
        d = sum - a - b - c;
        // if (a * b * c * d == sum) {
          cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d
               << endl;
        // }
      }
    }
  }
  return 0;
}