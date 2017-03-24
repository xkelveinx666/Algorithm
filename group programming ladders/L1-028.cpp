#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
void judge(int num) {
    int sqrtNum = round(sqrt(num));
    int index;
    if(num < 2) {
        cout<<"No"<<endl;
        return;
    }
    for(index = 2;index <= sqrtNum;index++) {
        if(num % index == 0) {
            cout<<"No"<<endl;
            return;
        }
    }
    cout<<"Yes"<<endl;
}
int main(void) {
  int n;
  cin >> n;
  while (n-- > 0) {
    int temp;
    cin >> temp;
    judge(temp);
  }
  return 0;
}