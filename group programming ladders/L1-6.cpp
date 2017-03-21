#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main(void) {
    int n, number, odd, even;
    odd = 0;
    even = 0;
    cin>>n;
    while(n--) {
        cin>>number;
        if(number % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }
    cout<<odd<<" "<<even;
    return 0;
}