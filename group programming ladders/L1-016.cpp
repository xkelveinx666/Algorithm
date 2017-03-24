#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
#define MAX 17
int getZ(string *s) {
    int array[] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    int index = 0;
    int sum = 0;
    for(;index < MAX;index++) {
        char temp = (*s)[index];
        if(temp < '0' || temp > '9') {
            return -1;
        }
        array[index] *= temp - '0';
        sum += array[index];
    }
    return sum%11;
} 
int main(void) {
    int times,index = 0,tempTimes,passIndex = 0;
    cin>>times;
    tempTimes = times;
    vector<string> vec(times);
    while(tempTimes-- >0) {
        cin>>vec[index++];
    }
    index = 0;
    tempTimes = times;
    while(tempTimes-- > 0) {
        string tempString = vec[index++];
        int z = getZ(&tempString);
        int length = tempString.length();
        if(z == -1) {
            cout<<tempString<<endl;
        } else {
            char m = 0;
            switch(z) {
                case 0:m = '1';break;
                case 1:m = '0';break;
                case 2:m = 'X';break;
                case 3:m = '9';break;
                case 4:m = '8';break;
                case 5:m = '7';break;
                case 6:m = '6';break;
                case 7:m = '5';break;
                case 8:m = '4';break;
                case 9:m = '3';break;
                case 10:m = '2';break;
            }
            if(tempString[length - 1] == m) {
                passIndex++;
            } else {
                cout<<tempString<<endl;
            }
        }
    }
    if(passIndex == times) {
        cout<<"All passed"<<endl;
    }
    return 0;
}