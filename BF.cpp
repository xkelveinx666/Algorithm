#include <iostream>
#include <string.h>
using namespace std;
#define MAXSIZE 100
void setString(char str[]) {
  str[0] = 1;
  cin >> str;
}
void getString(char str[]) { cout << str << endl; }
int bF(char parentStr[], char childStr[]) {
  int pLength = strlen(parentStr);
  int cLength = strlen(childStr);
  if (!(pLength && cLength)) {
    cout << "长度不匹配" << endl;
    return -1;
  }
  for (int pIndex = 0, pMax = pLength - cLength + 2; pIndex < pMax; pIndex++) {
    int i = pIndex;
    int cIndex = 0;
    for (; cIndex < cLength; cIndex++, i++) {
      if (parentStr[i] != childStr[cIndex]) {
        break;
      }
    }
    if (cIndex == cLength) {
      cout << "已找到对应子串, 该位置是" << endl;
      return pIndex;
    }
  }
  cout << "未找到匹配串" << endl;
  return -1;
}
int main(void) {
  char parentStr[MAXSIZE];
  char childStr[MAXSIZE];
  cout << "请输入两个字符串" << endl;
  setString(parentStr);
  setString(childStr);
  cout << "这两个字符串是" << endl;
  getString(parentStr);
  getString(childStr);
  cout << bF(parentStr, childStr) << endl;
}