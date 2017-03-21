#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

typedef struct {
  int no;
  double money;
  int number;
} packet;

bool compare(packet i, packet j) {
  if (i.money != j.money) {
    return i.money > j.money;
  } else if (i.number != j.number) {
    return i.number > j.number;
  } else {
    return i.no < j.no;
  }
}

int main(void) {
  int n, temp;
  cin >> n;
  vector<packet> vec(n + 1);
  for (int nIndex = 1; nIndex <= n; nIndex++) {
    vec[nIndex].no = nIndex;
    int k;
    cin >> k;
    while (k-- > 0) {
      int no, money;
      cin >> no >> money;
      vec[no].money += money;
      vec[no].number++;
      vec[nIndex].money -= money;
    }
  }
  sort(vec.begin() + 1, vec.end(), compare);
  std::vector<packet>::iterator it = vec.begin() + 1;
  for (; it != vec.end(); it++) {
    packet p = *it;
    printf("%d %.2lf\n", p.no, p.money / 100);
  }
  return 0;
}