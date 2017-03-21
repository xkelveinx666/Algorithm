#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
#define MAX_SIZE 10 
#define FIRST_NUMBER '0'
void initiateArray(int *numberArray) {
    int length = MAX_SIZE;
    while(length-- > 0) {
        numberArray[length] = 0;
    }
}

void judgeNumber(string number, int *numberArray) {
    int length = number.length();
    while(length-- > 0) {
        numberArray[(number[length] - FIRST_NUMBER)]++;
    }
    for(int naIndex = 0, naLength = MAX_SIZE;naIndex < naLength;naIndex++) {
        if(numberArray[naIndex] != 0) {
            cout<<naIndex<<':'<<numberArray[naIndex]<<endl;
        }
    }
}
int main(void) {
    string number;
    int numberArray[MAX_SIZE];
    initiateArray(numberArray);
    cin>>number;
    judgeNumber(number, numberArray);
    return 0;
}