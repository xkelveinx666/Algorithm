#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#include<vector>
#include<set>
#include<cstdio>
using namespace std;
int main(void) {
    double H;
    cin>>H;
    printf("%.1lf", (H - 100) * 0.9 * 2);
    return 0;
}