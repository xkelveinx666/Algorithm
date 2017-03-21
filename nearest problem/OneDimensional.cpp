#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define MAX_SIZE 10
#define MAX INT_MAX
#define pointer struct node *
struct node {
  int id;
  int x;
};
void input(vector<node> *vec) {
  int id = 1;
  int x;
  node *n;
  cout << "依次输入数据直到输入0结束" << endl;
  while (cin >> x && x != 0) {
    n = new node;
    n->id = id++;
    n->x = x;
    (*vec).push_back(*n);
  }
}
void output(vector<node> *vec) {
  vector<node>::iterator it = (*vec).begin();
  while (it != (*vec).end()) {
    cout << "id = " << it->id << " x = " << it->x << endl;
    it++;
  }
}
double computeLength(pointer p1, pointer p2) { return fabs(p2->x - p1->x); }
//对middle - 1 到middle + 1范围内计算最小长度
double theMinLength(vector<node> *vec, int minIndex, int maxIndex) {
  double minLength = computeLength(&(vec->at(minIndex)), &(vec->at(maxIndex)));
  while (minIndex < maxIndex) {
    int tempMinIndex = minIndex + 1;
    while (tempMinIndex < maxIndex) {
      double length =
          computeLength(&(vec->at(minIndex)), &(vec->at(tempMinIndex)));
      if (length < minLength) {
        minLength = length;
      }
      tempMinIndex++;
    }
    minIndex++;
  }
  return minLength;
}
double closest(vector<node> *vec, int start, int end) {
  if (end - start < 1) {
    return MAX;
  }
  int middle = (start + end) / 2;
  double leftSum = closest(vec, start, middle - 1);
  double rightSum = closest(vec, middle + 1, end);
  double middleSum = theMinLength(vec, middle - 1, middle + 1);
  double min = leftSum < rightSum ? leftSum : rightSum;
  min = min < middleSum ? min : middleSum;
  return min;
}
bool compare(node i, node j) { return i.x < j.x; }
int main(void) {
  vector<node> vec;
  input(&vec);
  sort(vec.begin(), vec.end(), compare);
  cout << "the closesting distance is " << closest(&vec, 0, vec.size() - 1)
       << endl;
  return 0;
  //-20 11 -46 13 -5 -2  7 -10 0     2
  //-20 11 -46 13 -5 -2  -11 18  7 10 100 30 26 -60 31 15 78 3 -9 6 0      1
}