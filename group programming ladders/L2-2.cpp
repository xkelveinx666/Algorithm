#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef struct {
  set<int> friendly;
  set<int> enemy;
} relation;
int main(void) {
  int n, m, k;
  cin >> n >> m >> k;
  vector<relation> people(n + 1);
  while (m-- > 0) {
    int p1, p2, r;
    cin >> p1 >> p2 >> r;
    if (r == 1) {
      people[p1].friendly.insert(p2);
      people[p2].friendly.insert(p1);
    } else {
      people[p1].enemy.insert(p2);
      people[p2].enemy.insert(p1);
    }
  }
  while (k-- > 0) {
    int p1, p2;
    cin >> p1 >> p2;
    relation r1 = people[p1];
    relation r2 = people[p2];
    set<int> rf1 = r1.friendly;
    set<int> re1 = r1.enemy;
    set<int> rf2 = r2.friendly;
    set<int> re2 = r2.enemy;
    set<int> unionFriendly;
    set_intersection(rf1.begin(), rf1.end(), rf2.begin(), rf2.end(),
                     inserter(unionFriendly, unionFriendly.begin()));
    std::set<int>::iterator it = unionFriendly.begin();
    if (rf1.count(p2) == 1 && re1.count(p2) == 0) {
      cout << "No problem" << endl;
    } else if (re1.count(p2) == 1) {
      if (unionFriendly.empty()) {
        cout << "No way" << endl;
      } else {
        cout << "OK but..." << endl;
      }
    } else {
      cout << "OK" << endl;
    }
  }
  return 0;
}