#include <iostream>
using namespace std;
long multiplication(int m, int n) {
  long sum = 0;
  while (n != 1) {
    if (n % 2 == 0) {
      n = n >> 1;
    } else {
      n = (n - 1) >> 1;
      sum += m;
    }
    m = m << 1;
    cout << "m = " << m << " n = " << n << endl;
  }
  return m * n + sum;
}
int main(void) {
  long m, n;
  cout << "请输入m和n" << endl;
  cin >> m >> n;
  long result = multiplication(m, n);
  cout << "result = " << result << endl;
  return 0;
}