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
  int y;
};
void input(vector<node> *vec) {
  int id = 1;
  int x, y;
  node *n;
  cout << "依次输入数据直到输入0结束" << endl;
  while (cin >> x && x != 0 && cin >> y && y != 0) {
    n = new node;
    n->id = id++;
    n->x = x;
    n->y = y;
    (*vec).push_back(*n);
  }
}
void output(vector<node> *vec) {
  vector<node>::iterator it = (*vec).begin();
  while (it != (*vec).end()) {
    cout << "id = " << it->id << " x = " << it->x << " y = " << it->y << endl;
    it++;
  }
}
//用于找出已middleIndex为中心,距离为distance的左右边下标
void getIndex(vector<node> *vec, int distance, int middleIndex, int *min,
              int *max, int left, int right) {
  int minIndex = middleIndex;
  int maxIndex = middleIndex;
  distance = ceil(distance);
  node middleNode = vec->at(middleIndex);
  node nextNode = vec->at(maxIndex);
  node preNode = vec->at(minIndex);
  while (abs(nextNode.x - middleNode.x) < distance && maxIndex < right) {
    maxIndex++;
    nextNode = vec->at(maxIndex);
  }
  while (abs(preNode.x - middleNode.x) < distance && minIndex > left) {
    minIndex--;
    preNode = vec->at(minIndex);
  }
  *min = minIndex;
  *max = maxIndex;
}
//计算两点间的距离
double computeLength(pointer start, pointer end) {
  double x = end->x - start->x;
  double y = end->y - start->y;
  return sqrt(x * x + y * y);
}
//在范围为distance中心为middleIndex,左边为minIndex,右边为maxIndex的范围内计算出最小距离的点
double computeTheMinLength(vector<node> *vec, int distance, int middleIndex,
                        int minIndex, int maxIndex) {
  double minLength = computeLength(&(vec->at(minIndex)), &(vec->at(maxIndex)));
  while (minIndex < middleIndex) {
    int tempMaxIndex = maxIndex;
    node p1Node = vec->at(minIndex);
    while (tempMaxIndex > middleIndex) {
      node p2Node = vec->at(maxIndex);
      if (abs(p1Node.y - p2Node.y) <= distance) {
        double length = computeLength(&(vec->at(minIndex)), &(vec->at(maxIndex)));
        if (length < minLength) {
          minLength = length;
        }
      }
      tempMaxIndex--;
    }
    minIndex++;
  }
  return minLength;
}
//递归找到两个点为止,并返回每个区域最小值
double closest(vector<node> *vec, int start, int end) {
  if (end - start < 1) {
    return MAX;
  }
  int middle = (start + end) / 2;
  double leftSum = closest(vec, start, middle - 1);
  double rightSum = closest(vec, middle + 1, end);
  double min = leftSum < rightSum ? leftSum : rightSum;
  int minIndex = 0;
  int maxIndex = 0;
  getIndex(vec, min, middle, &minIndex, &maxIndex, start, end);
  double middleSum = computeTheMinLength(vec, min, middle, minIndex, maxIndex);
  min = min < middleSum ? min : middleSum;
  return min;
}
//排序,先按x轴排序再按y轴排序
bool compare(node i, node j) {
  if (i.x != i.x) {
    return i.x < j.x;
  } else {
    return i.y < j.y;
  }
}
int main(void) {
  vector<node> vec;
  input(&vec);
  cout << "sorting" << endl;
  sort(vec.begin(), vec.end(), compare);
  cout << "The closest distance is " << closest(&vec, 0, vec.size() - 1) << endl;
  return 0;
  //-20 11 -46 13 -5 -2  -11 18  7 10 15 30  100 30 26 15 -60 31 15 78 3 100 4 6 -9 6 0 5
  //-20 11 -46 13 0 26.078
}