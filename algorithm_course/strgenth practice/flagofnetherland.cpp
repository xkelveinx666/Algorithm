#include<iostream>
#include<string.h>
using namespace std;
#define MAXSIZE 100
#define firstChar 'R'
#define secondChar 'W'
#define thirdChar 'B'
void showNumber(char flag[]) {
    int n = strlen(flag);
    for(int i = 0;i < n;i++) {
        cout<<flag[i];
    }
    cout<<endl;
}
void sort(char originalFlag[] , char newFlag[]) {
    int n = strlen(originalFlag);
    int fNumber = 0;
    int sNumber = 0;
    int tNUmber = 0;
    for(int i = 0;i < n;i++) {
        switch(originalFlag[i]) {
            case firstChar:fNumber++;break;
            case secondChar:sNumber++;break;
            case thirdChar:tNUmber++;break;
            default:cout<<"only "<<firstChar<<secondChar<<thirdChar<<endl;return;
        }
    }
    int i = 0;
    while(fNumber-- > 0) {
        newFlag[i++] = firstChar;
    }
    while(sNumber-- > 0) {
        newFlag[i++] = secondChar;
    }
    while(tNUmber-- > 0) {
        newFlag[i++] = thirdChar;
    }
    newFlag[i] = '\0';
}
int main(void) {
    char originalFlag[MAXSIZE];
    char newFlag[MAXSIZE];
    cin>>originalFlag;
    cout<<"this originalFlag is "<<endl;
    showNumber(originalFlag);
    cout<<"sorting"<<endl;
    sort(originalFlag, newFlag);
    showNumber(newFlag);
    return 0;
}