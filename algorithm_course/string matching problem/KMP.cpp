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

void initiateNextArray(int next[], int length) {
  int nIndex = 0;
  next[nIndex++] = -1;
  for (; nIndex < length; nIndex++) {
    next[nIndex] = 0;
  }
  next[nIndex] = '\0';
}

void getNextArray(char str[], int next[]) {
  int cLength = strlen(str);
  //将next数组初始化,第一位为-1,长度位置设为'\0',其他位置设为0
  initiateNextArray(next, cLength);
  //趟数，从第二个下标到最后
  for (int lapsIndex = 1, lapsMax = cLength; lapsIndex < lapsMax; lapsIndex++) {
    //子数组从长度为1到长度为母数组长度减1
    for (int sonIndex = 1, sonMax = lapsIndex + 1; sonIndex < sonMax;
         sonIndex++) {
      //每个长度数组找前后缀起始处，往后比较
      int sufIndex = 0, postIndex = cLength - sonIndex;
      for (; sufIndex < sonIndex && postIndex < cLength;
           sufIndex++, postIndex++) {
        if (str[sufIndex] != str[postIndex]) {
          break;
        }
      }
      //若长度范围内均能匹配则next设为能匹配前后缀的长度
      if (sufIndex == sonIndex && postIndex == cLength) {
        next[lapsIndex] = sonIndex;
      }
    }
  }
  cout << next[0] << " " << next[1] << " " << next[2] << " " << next[3] << " " << next[4] << " " << endl;
}

int kmp(char parentStr[], char childStr[], int next[]) {
  int pLength = strlen(parentStr);
  int cLength = strlen(childStr);
  for (int pIndex = 0, cIndex = 0, pMax = pLength - cLength + 2;
       pIndex < pMax;) {
    for (; cIndex < cLength; cIndex++, pIndex++) {
      if (parentStr[pIndex] != childStr[cIndex]) {
        break;
      }
    }
    if (cIndex == cLength) {
      cout << "已找到匹配信息" << endl;
      return pIndex - cLength;
    } else {
    //将子串下标返回到所对称的前一个位置
      cIndex = next[cIndex] - 1;
      if (cIndex <= 0) {
        pIndex++;
        cIndex = 0;
      }
    }
  }
  cout << "未找到匹配信息" << endl;
  return -1;
}
int main(void) {
  char parentStr[MAXSIZE];
  char childStr[MAXSIZE];
  int nextArray[MAXSIZE];
  cout << "请输入两个字符串" << endl;
  setString(parentStr);
  setString(childStr);
  cout << "这两个字符串是" << endl;
  getString(parentStr);
  getString(childStr);
  getNextArray(childStr, nextArray);
  cout << kmp(parentStr, childStr, nextArray) << endl;
}