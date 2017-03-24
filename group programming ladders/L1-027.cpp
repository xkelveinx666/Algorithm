#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<cstdio>
#include<string>
#include<cmath>
#include<cstring>
using namespace std;
bool compare(int i, int j) {
    return i > j;
}
int main(void) {
    string phoneNo;
    cin>>phoneNo;
    set<int> phoneSet;
    int max = phoneNo.length();
    for(int i = 0;i < max;i++) {
        phoneSet.insert(phoneNo[i] - '0');
    }
    set<int>::iterator begin = phoneSet.begin();
    set<int>::iterator end = phoneSet.end();
    vector<int> phoneVector;
    while(begin != end) {
        phoneVector.push_back(*begin);
        begin++;
    }
    sort(phoneVector.begin(), phoneVector.end(), compare);
    vector<int>::iterator beginV = phoneVector.begin();
    vector<int>::iterator endV = phoneVector.end();
    cout<<"int[] arr = new int[]{"<<*beginV;
    beginV++;
    while(beginV != endV) {
        cout<<","<<*beginV;
        beginV++;
    }
    cout<<"};"<<endl;
    cout<<"int[] index = new int[]{";
    beginV = phoneVector.begin();
    vector<int>::iterator v = find(beginV, endV, phoneNo[0] - '0');
        cout<<distance(beginV, v);
    for(int i = 1;i < max;i++) {
        vector<int>::iterator v = find(beginV, endV, phoneNo[i] - '0');
        cout<<","<<distance(beginV, v);
    }
    cout<<"};"<<endl;
    return 0;
}