#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<set>
using namespace std;
int main(void) {
    int d;
    cin>>d;
    if(d == 7) {
        cout<<2<<endl;
    }
    else if(d > 5) {
        cout<<7 - d<<endl;
    } else {
        cout<<d + 2 <<endl;
    }
    return 0;
}