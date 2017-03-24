#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define pointer people *
#define N 10000
string leftPad(int length, char ch, string *s) {
    string originalStr = *s;
    int originalLength = originalStr.length();
    if(originalLength < length) {
        string str(length - originalLength, ch);
        return str + *s;
    } else if(originalLength == length){
        return originalStr;
    } else {
        char array[N];
        int j = 0;
        for(int i = originalLength - length;i < originalLength;j++,i++) {
            array[j] = originalStr[i];
        }
        string str(array, j);
        return str;
    }
}
int main(void) {
  int length;
  char ch;
  string str;
  cin >> length >> ch;
  getchar();
  getline(cin, str);
  cout << leftPad(length, ch, &str) << endl;
  return 0;
}