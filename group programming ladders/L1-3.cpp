#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;

void judgeFall(int aAvailable,int bAvailable,int times) {
    int aCall,bCall;
    int aNum,bNum;
    int sum;
    int aCount = 0,bCount = 0;
    while(times--> 0 && aAvailable >= 0 && bAvailable >= 0) {
        cin>>aCall>>aNum>>bCall>>bNum;
        sum = aCall + bCall;
        if((aNum != sum && bNum != sum )||( aNum == sum && bNum == sum)) {
            continue;
        } else {
            if(aNum == sum && bNum != sum) {
                aCount++;
                aAvailable--;
            } else if(aNum != sum && bNum == sum){
                bCount++;
                bAvailable--;
            }
        }
    }
    if(aAvailable < 0) {
        cout<<"A"<<endl;
        cout<<bCount<<endl;
    } else {
        cout<<"B"<<endl;
        cout<<aCount<<endl;
    }
}
int main(void) {
    int aAvailable,bAvailable;
    cin>>aAvailable>>bAvailable;
    int times;
    cin>>times;
    judgeFall(aAvailable,bAvailable,times);
    return 0;
}