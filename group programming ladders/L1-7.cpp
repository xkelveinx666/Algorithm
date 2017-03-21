#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
void printGPLT(string str) {
    int gNumber = 0, pNumber = 0, lNumber = 0, tNumber = 0;
    for(int index = 0,length = str.length();index < length;index++) {
        switch(str[index]) {
            case 'g':;
            case 'G':gNumber++;break;
            case 'p':;
            case 'P':pNumber++;break;
            case 'l':;
            case 'L':lNumber++;break;
            case 't':;
            case 'T':tNumber++;break;
        }
    }
    while(gNumber > 0 || pNumber > 0 || lNumber > 0 || tNumber > 0) {
        if(gNumber != 0) {
            gNumber--;
            cout<<"G";
        }
        if(pNumber != 0) {
            pNumber--;
            cout<<"P";
        }
        if(lNumber != 0) {
            lNumber--;
            cout<<"L";
        }
        if(tNumber != 0) {
            tNumber--;
            cout<<"T";
        }
    }
}
int main(void) {
    string str;
    cin>>str;
    printGPLT(str);
    return 0;
}