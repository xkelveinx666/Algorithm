#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MAX 1001
int getResult(char array[]) {
  int length = strlen(array);
  int result = 0;
  for (int i = 0; i < length; i++) {
    if (array[i] < '0' || array[i] > '9') {
      return 0;
    }
  }
  sscanf(array, "%d", &result);
  if (result <= 1000 && result >= 1) {
    return result;
  }
  return 0;
}
int main(void) {
  char a[MAX], b[MAX];
  cin >> a;
  getchar();
  gets(b);
  int sum = 0;
  int resultA = getResult(a);
  int resultB = getResult(b);
  if (resultA) {
    cout << resultA << " + ";
    sum += resultA;
  } else {
    cout << "? + ";
  }
  if (resultB) {
    cout << resultB << " = ";
    sum += resultB;
  } else {
    cout << "? = ";
  }
  if (resultA && resultB) {
    cout << sum << endl;
  } else {
    cout << "?" << endl;
  }
  return 0;
}