#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define judgeNumber '2'
int coutChar(string number, char ch) {
  int count = 0;
  for (int nIndex = 0, nMax = number.length(); nIndex < nMax; nIndex++) {
    if (number[nIndex] == ch) {
      count++;
    }
  }
  return count;
}
double judgeTwo(string number) {
  double countNumber;
  double length = number.length();
  double multiple = 10000;
  countNumber = coutChar(number, judgeNumber);
  if (countNumber == 0) {
    cout<<"0.00%"<<endl;
    return 0;
  }
  if (multiple == 0) {
    return 0;
  }
  if (number[0] == '-') {
    length--;
    multiple *= 1.5;
  }
  if (number[number.length() - 1] % 2 == 0) {
    multiple *= 2;
  }
  double result = countNumber / length * multiple;
  result = ::round(result);
  result /= 100;
  printf("%.2f", result);
  cout << "%";
  return countNumber / length * multiple;
}
int main(void) {
  string number;
  cin >> number;
  judgeTwo(number);
  return 0;
}