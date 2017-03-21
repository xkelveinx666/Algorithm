#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define FIRST_NUMBER '0'
void getTime(string timeString, int *hour, int *mintues) {
  *hour = (timeString[0] - FIRST_NUMBER) * 10 + timeString[1] - FIRST_NUMBER;
  *mintues = (timeString[3] - FIRST_NUMBER) * 10 + timeString[4] - FIRST_NUMBER;
}
void showTime(int hour, int mintues) {
  if (hour < 10) {
    cout << "0" << hour;
  } else {
    cout << hour;
  }
  cout << ':';
  if (mintues < 10) {
    cout << "0" << mintues;
  } else {
    cout << mintues;
  }
}
void judgeTime(string timeString, int hour, int mintues) {
  if (hour <= 12) {
    cout << "Only " << timeString << ".  Too early to Dang." << endl;
    return;
  }
  hour -= 12;
  while (hour-- > 0) {
    cout << "Dang";
  }
  if (mintues > 0) {
    cout << "Dang";
  }
  cout << endl;
}
int main(void) {
  string timeString;
  cin >> timeString;
  int hour;
  int mintues;
  getTime(timeString, &hour, &mintues);
  judgeTime(timeString, hour, mintues);
  return 0;
}