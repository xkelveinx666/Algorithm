#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define pointer struct student *
#define N 51
struct student {
  int sex;
  string name;
  bool hasFound;
};
int main(void) {
  int n;
  cin >> n;
  int backupN = n;
  student stuArray[N];
  vector<student> vec(n);
  vector<string> vecName;
  int index = 0;
  while (n-- > 0) {
    pointer s = new student;
    cin >> s->sex;
    cin >> s->name;
    s->hasFound = false;
    stuArray[index++] = *s;
  }
  n = backupN;
  for(int i = 0;i < n;i++) {
    pointer pi = &stuArray[i];
    for(int j = n - 1;j > i;j--) {
      pointer pj = &stuArray[j];
      if(!pj -> hasFound && pj -> sex != pi -> sex) {
        pj -> hasFound = true;
        pi -> hasFound = true;
        vecName.push_back(pi->name + " " + pj->name);
        break;
      }
    }
  }
  vector<string>::iterator beginName = vecName.begin();
  vector<string>::iterator endName = vecName.end();
  while (beginName != endName) {
    cout << *beginName << endl;
    beginName++;
  }
  return 0;
}