#include <iostream>
#include <string.h>
using namespace std;
#define MAXSIZE 9
void showNumber(char number[]) {
  int n = strlen(number);
  for (int i = 0; i < n; i++) {
    cout << number[i];
  }
  cout << endl;
}

//将数组中的数据转化成能计算的对应位置的数字
bool arrayToNumber(char numberArray[], double *multiplyLeft,
                   double *mutiplyRight, double *divisionLeft,
                   double *divisionRight, double *subtrationRight) {
  if (numberArray[2] == '1' || numberArray[6] == '1') {
    return false;
  }
  *multiplyLeft = (numberArray[0] - '0') * 10 + (numberArray[1] - '0');
  *mutiplyRight = (numberArray[2] - '0');
  *divisionLeft = (numberArray[3] - '0') * 100 + (numberArray[4] - '0') * 10 +
                  (numberArray[5] - '0');
  *divisionRight = (numberArray[6] - '0');
  *subtrationRight = (numberArray[7] - '0') * 10 + (numberArray[8] - '0');
  return true;
}

void swap(char *left, char *right) {
  char temp = *left;
  *left = *right;
  *right = temp;
}

//递归进行全排列
void allRange(char str[], int start, int length) {
  if (start == length - 1) {
    double ml, mr, dl, dr, sr;
    double *multiplyLeft = &ml, *mutiplyRight = &mr, *divisionLeft = &dl,
           *divisionRight = &dr, *subtrationRight = &sr;
    if (arrayToNumber(str, multiplyLeft, mutiplyRight, divisionLeft,
                      divisionRight, subtrationRight)) {
      if (ml * mr + dl / dr - sr == 0) {
        cout<<"已找到数据"<<endl;
        cout << ml << "*" << mr << "+" << dl << "/" << dr << "-" << sr <<"="<<ml * mr + dl / dr - sr<<endl;
      }
    }
  } else {
    for (int i = start; i <= length - 1;
         i++) { //从下标为start的数开始，分别与它后面的数字交换
      swap(&str[start], &str[i]);
      allRange(str, start + 1, length);
      swap(&str[start], &str[i]);
    }
  }
}

int main(void) {
  char numberArray[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
  showNumber(numberArray);
  //   changePlace(numberArray);
  allRange(numberArray, 0, strlen(numberArray));
  return 0;
}