#include <iostream>
#include <string.h>
using namespace std;
#define MAXSIZE 100
void setString(char str[]) {
  str[0] = 1;
  cin >> str;
}
void getString(char str[]) { cout << str << endl; }
int getDist(char *str, char ch) {
  int strIndex = (int)strlen(str) - 1;
  int strMin = 0;
  for (; strIndex >= strMin; strIndex--) {
    if (str[strIndex] == ch) {
      break;
    }
  }
  if (strIndex == strMin || strIndex == strlen(str) - 1) {
    return (int)strlen(str) - 1;
  } else {
    return (int)strlen(str) - strIndex - 1;
  }
}
int bM(char parentStr[], char childStr[]) {
  int pLength = (int)strlen(parentStr);
  int cLength = (int)strlen(childStr);
  if (!(pLength && cLength)) {
    cout << "长度不匹配" << endl;
    return -1;
  }
  for (int pIndex = cLength - 1, pMax = pLength - cLength + 2, cMin = 0,
           cIndex = 0, distance = 0, i = 0;
       pIndex < pMax; pIndex = i + distance) {
    i = pIndex;
    cIndex = cLength - 1;
    for (; cIndex >= cMin; cIndex--, i--) {
      if (parentStr[i] != childStr[cIndex]) {
        break;
      }
    }
    if (cIndex == cMin - 1) {
      int result = pIndex - cLength + 1;
      cout << "已找到对应子串, 该位置是" << result << endl;
      return result;
    } else {
      distance = getDist(childStr, parentStr[i]);
    }
  }
  cout << "未找到匹配串" << endl;
  return -1;
}
int main(void) {
  //   const char *parentStr = "ababcabcacbab";
  //   const char *childStr = "abcac";
  char parentStr[MAXSIZE];
  char childStr[MAXSIZE];
  cout << "请输入两个字符串" << endl;
  setString(parentStr);
  setString(childStr);
  cout << "这两个字符串是" << endl;
  getString(parentStr);
  getString(childStr);
  bM(parentStr, childStr);
}
/*
ababcabcacbab
abcac
*/
