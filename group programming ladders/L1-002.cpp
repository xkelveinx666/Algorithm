#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int judgeMaxNumber(int number, int *countNumber) {
  int count = 1;
  int maxNumber = -1;
  while (maxNumber + count * 2 <= number) {
    maxNumber += count * 2;
    count += 2;
  }
  *countNumber = count - 2;
  return maxNumber;
}

void printHourGlass(int number, char ch) {
  int countNumber;
  int maxNumber = judgeMaxNumber(number, &countNumber);
  int restNumber = number - maxNumber;
  int totalCountNumber = countNumber;
  while (countNumber > 0) {
    //先计算空格
    int length = (totalCountNumber - countNumber) / 2.0;
    while (length-- > 0) {
      cout << " ";
    }
    //再计算输出字符
    length = countNumber;
    while (length-- > 0) {
      cout << ch;
    }
    cout << endl;
    countNumber -= 2;
  }
  countNumber += 2;
  while (countNumber < totalCountNumber) {
    countNumber += 2;
    int length = (totalCountNumber - countNumber) / 2.0;
    while (length-- > 0) {
      cout << " ";
    }
    length = countNumber;
    while (length-- > 0) {
      cout << ch;
    }
    cout << endl;
  }
  cout << restNumber << endl;
}

int main(void) {
  int number;
  char ch;
  cin >> number;
  if (number == 0) {
    return 0;
  }
  cin >> ch;
  printHourGlass(number, ch);
  return 0;
}