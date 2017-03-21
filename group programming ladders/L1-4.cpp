#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
set<string> idSet;
void addPeople() {
  int k;
  cin >> k;
  string id;
  if(k < 2) {
    cin>>id;
    return;
  }
  while (k-- > 0) {
    cin >> id;
    if (idSet.count(id) == 0) {
      idSet.insert(id);
    }
  }
}
int main(void) {
  int n, m;
  cin >> n;
  string strTemp;
  set<string> resultSet;
  vector<string> resultVector;
  while (n-- > 0) {
    addPeople();
  }
  cin >> m;
  while (m-- > 0) {
    cin >> strTemp;
    if(idSet.count(strTemp) == 0 && resultSet.count(strTemp) == 0) {
        resultVector.push_back(strTemp);
        resultSet.insert(strTemp);
    }
  }
  if(resultSet.size() == 0) {
    cout<<"No one is handsome"<<endl;
    return 0;
  }
  vector<string>::iterator it = resultVector.begin();
  cout<<*it;
  for(it++;it != resultVector.end();it++) {
    cout<<" "<<*it;
  }
  return 0;
}