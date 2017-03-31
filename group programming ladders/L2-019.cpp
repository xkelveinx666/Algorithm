#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#include<vector>
using namespace std;
#define pointer struct NoFocus *
struct NoFocus{
    string name;
    int praise;
};
bool compare(pointer p, pointer q) {
    return p -> name < q -> name; 
}
int main(void) {
    int n;
    cin>>n;
    set<string> focusSet;
    vector<pointer> noFocusVector;
    int sum = 0;
    //将所有名字存入set中
    while(n-- > 0) {
        string name;
        cin>>name;
        focusSet.insert(name);
    }
    cin>>n;
    int tempN = n;
    //利用之前set判断名字是否已存在，保存不存在的名字
    while(tempN-- > 0) {
        string name;
        int praise;
        cin>>name>>praise;
        sum += praise;
        if(focusSet.count(name) == 0) {
            pointer p = new NoFocus;
            p -> name = name;
            p -> praise = praise;
            noFocusVector.push_back(p);
        }
    }
    bool outputFlag = false;
    sum /= n;
    //已名字升序排序
    sort(noFocusVector.begin(), noFocusVector.end(), compare);
    auto beginIt = noFocusVector.begin();
    auto endIt = noFocusVector.end();
    //输出名字,若没有输出则输出并没有
    while(beginIt != endIt) {
        pointer p = *beginIt;
        if(p -> praise > sum) {
            outputFlag = true;
            cout<<p -> name<<endl;
        }
        beginIt++;
    }
    if(!outputFlag) {
        cout<<"Bing Mei You"<<endl;
    }
    return 0;
}
