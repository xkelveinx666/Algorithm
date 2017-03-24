#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;
#define pointer people *
#define N 20
struct people {
    int height;
    int realWeight;
    int normalWeight;
};
double getWeight(int height) {
    return (double)(height - 100) * 0.9 * 2;
}
void judgePerfect(double normalWeight, double realWeight) {
    double ratio = (realWeight - normalWeight) / normalWeight;
    if(fabs(ratio) < 0.1) {
        cout<<"You are wan mei!"<<endl;
    } else if(realWeight > normalWeight) {
        cout<<"You are tai pang le!"<<endl;
    } else {
        cout<<"You are tai shou le!"<<endl;
    }
}
int main(void) {
    int n;
    cin>>n;
    int index = 0;
    while(n-- > 0) {
        pointer p = new people;
        cin >> p -> height;
        cin >> p -> realWeight;
        p -> normalWeight = getWeight(p -> height);
        judgePerfect(p -> normalWeight, p -> realWeight);
        delete p;
    }
    return 0;
}