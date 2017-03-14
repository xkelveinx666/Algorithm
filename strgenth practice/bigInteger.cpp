#include<iostream>
#include<string.h>
using namespace std;
#define MAXSIZE 100

void showNumber(char number[]) {
    int n = strlen(number);
    for(int i = 0;i < n;i++) {
        cout<<number[i];
    }
    cout<<endl;
}

bool jugdeDivedeByEleven(char number[]) {
    int n = strlen(number) + 1;
    int sum = 0;
    while((n - 2)> 0) {
        int temp;
        n -= 2;
        if(number[n - 1] > '9' || number[n - 1] < '0' || number[n] > '9' || number[n - 1] < '0') {
            cout<<"number only"<<endl;
            return false;
        }
        temp = (int)(number[n - 1]- '0') * 10;
        temp += (int)(number[n] - '0');
        sum += temp;
    }
    if(n - 1 != 0) {
        sum += (int)(number[0] - '0');
    }
    cout<<"sum = "<<sum<<endl;
    if(sum % 11  == 0) {
        cout<<"yes"<<endl;
        return false;
    } else {
        cout<<"no"<<endl;
        return true;
    }
}
int main(void) {
    char number[MAXSIZE];
    cin>>number;
    cout<<"this number is "<<endl;
    showNumber(number);
    cout<<"juding"<<endl;
    jugdeDivedeByEleven(number);
    return 0;
}