#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MAX 8
#define cpointer struct coin *
struct coin {
  int value;
};
void initiate(vector<cpointer> *c) {
  vector<cpointer> coins = *c;
  srand((unsigned)time(NULL));
  int fakeIndex = rand() % MAX;
  cout << fakeIndex << endl;
  for (int i = 0; i < MAX; i++) {
    cpointer cp = new coin;
    cp->value = 1;
    coins.push_back(cp);
  }
  coins[fakeIndex]->value = 0;
  *c = coins;
}

int getSum(vector<cpointer> *c, int start, int end) {
  vector<cpointer> coins = *c;
  int sum = 0;
  for(;start <= end;start++) {
    sum += coins[start] -> value;
  }
  return sum;
}
int splitCoins(vector<cpointer> *c, int start, int end) {
  int totalLength = (end - start) + 1;
  if (totalLength < 3) {
    vector<cpointer> coins = *c;
    int middle = coins[start + 1]->value;
    int left;
    if(start - 1 >= 0) {
      left = coins[start]->value;
    } else {
      left = middle;
    }
    int right = coins[end]->value;
    if (left == middle && left == right) {
      return -1;
    }
    if (left == middle) {
      return end;
    } else if (left == right) {
      return start + 1;
    } else {
      return start;
    }
  }
  int halfLength = totalLength / 2;
  bool oddFlag = 2 * halfLength < totalLength ? true : false;
  int outLength = halfLength / 3;
  int middleIndex = start + halfLength - 1;
  int leftMidIndex = middleIndex - outLength * 2;
  int leftSum1 = getSum(c, start, leftMidIndex);
  int leftSum2 = getSum(c, leftMidIndex + 1, middleIndex - outLength);
  if (oddFlag) {
    middleIndex++;
  }
  int rightMidIndex = end - outLength * 2;
  int rightSum1 = getSum(c, middleIndex + 1, rightMidIndex);
  int rightSum2 = getSum(c, rightMidIndex + 1, rightMidIndex + outLength);
  int leftSum = leftSum1 + leftSum2;
  int rightSum = rightSum1 + rightSum2;
  cout<<"ls = "<<leftSum<<" rs = "<<rightSum<<endl;
  if (leftSum == rightSum) {
    cout<<"LMI = "<<leftMidIndex<<" MI = "<<middleIndex<<" RMI ="<<rightMidIndex<<" END = "<<end<<endl;
    int result1 = splitCoins(c, leftMidIndex, middleIndex);
    int result2 = splitCoins(c, rightMidIndex - 1, end);
    if (result1 == -1) {
      return result2;
    } else {
      return result1;
    }
  } else {
    int changeLeftSum = leftSum1 + rightSum2;
    int changeRightSum = rightSum1 + leftSum2;
    cout<<"cls = "<<changeLeftSum<<" crs = "<<changeRightSum<<endl;
    if (changeLeftSum - changeRightSum == leftSum - rightSum) {
      int result1 = splitCoins(c, start, leftMidIndex + 1);
      int result2 = splitCoins(c, middleIndex + 1, rightMidIndex + 1);
      if (result1 == -1) {
        return result2;
      } else {
        return result1;
      }
    } else {
      int result1 =
          splitCoins(c, leftMidIndex + 1, middleIndex - outLength + 1);
      int result2 =
          splitCoins(c, rightMidIndex + 1, rightMidIndex + outLength + 1);
      if (result1 == -1) {
        return result2;
      } else {
        return result1;
      }
    }
  }
}
int main(void) {
  vector<cpointer> coins;
  initiate(&coins);
  auto begin = coins.begin();
  auto end = coins.end();
  while (begin != end) {
    cpointer cp = *begin;
    cout << cp->value << " ";
    begin++;
  }
  cout<<endl;
  cout<<"result = "<<splitCoins(&coins, 0, coins.size() - 1)<<endl;
  return 0;
}