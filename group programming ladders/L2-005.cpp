#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define pointer struct parent *
struct parent {
  string id;
  int sonNum;
  set<string> *all;
  int home;
  int size;
};
bool compare(parent p1,parent p2) {
  return p1.id < p2.id;
}
int main(void) {
  int n;
  cin >> n;
  vector<pointer> vec;
  while (n-- > 0) {
    string id;
    string father;
    string mother;
    pointer p = new parent;
    set<string> allV;
    cin >> id >> father >> mother >> p->sonNum;
    p->id = id;
    allV.insert(id);
    allV.insert(father);
    allV.insert(mother);
    int tempSonNum = p->sonNum;
    while (tempSonNum-- > 0) {
      string son;
      cin >> son;
      allV.insert(son);
    }
    p->all = &allV;
    cin >> p->home >> p->size;
    vec.push_back(p);
  }
  vector<pointer>::iterator begin = vec.begin();
  vector<pointer>::iterator end = vec.end();
  while(begin != end) {
    pointer p = *begin;
    auto tempBegin = begin + 1;
    while(tempBegin != end) {
      pointer q = *tempBegin;
      set<string> sp = *(p->all);
      set<string> sq = *(q->all);
      set<string> s;
      set_intersection(sp.begin(),sp.end(),sq.begin(),sq.end(),inserter(s, s.begin()));
      if(s.size() != 0) {
        s.clear();
        set_union(sp.begin(),sp.end(),sq.begin(),sq.end(),inserter(s,s.begin()));
      }
      p->all = &s;
      p->all = &s;
      tempBegin++;
    }
  }
  return 0;
}