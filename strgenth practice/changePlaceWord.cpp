#include<iostream>
#include<string.h>
using namespace std;
#define MAXSIZE 100
#define TOTALCHAR 26
void showNumber(char word[]) {
    int n = strlen(word);
    for(int i = 0;i < n;i++) {
        cout<<word[i];
    }
    cout<<endl;
}
bool equalsCharArray(char firstWord[] , char secondWord[], int m , int n) {
    for(int i = 0;i < m;i++) {
        if(firstWord[i] != secondWord[i]) {
            return false;
        }
    }
    return true;
}

bool equalsIntegerArray(int firstArray[] , int secondArray[], int m , int n) {
    for(int i = 0;i < m;i++) {
        if(firstArray[i] != secondArray[i]) {
            return false;
        }
    }
    return true;
}
bool similar(char firstWord[] , char secondWord[], int m , int n) {
    int number1[TOTALCHAR];
    int number2[TOTALCHAR];
    for(int i = 0;i < TOTALCHAR;i++) {
       number1[i] = 0;
       number2[i] = 0;
    }
    for(int i = 0;i < m;i++) {
       number1[(firstWord[i] - 'a')]++;
       number2[(secondWord[i] - 'a')]++;
    }
    if(equalsIntegerArray(number1 , number2, TOTALCHAR, TOTALCHAR) == 1) {
        return true;
    } else {
        return false;
    }
}
bool judegeWord(char firstWord[] , char secondWord[]) {
    int m = strlen(firstWord);
    int n = strlen(secondWord);
    if( m != n) {
        cout<<"the lengths of two words is different"<<endl;
        return false;
    }
    if(equalsCharArray(firstWord, secondWord, m, n) == 1) {
        cout<<"the two words is same"<<endl;
        return false;
    }
    if(similar(firstWord, secondWord, m, n) == 1) {
        cout<<"yes"<<endl;
        return true;
    } else {
        cout<<"no"<<endl;
        return false;
    }
}
int main(void) {
    char firstWord[MAXSIZE];
    char secondWord[MAXSIZE];
    cout<<"please enter the first word"<<endl;
    cin>>firstWord;
    cout<<"please enter the second word"<<endl;
    cin>>secondWord;
    cout<<"the first word is "<<endl;
    showNumber(firstWord);
    cout<<"the second word is "<<endl;
    showNumber(secondWord);
    cout<<"juding"<<endl;
    judegeWord(firstWord, secondWord);
    return 0;
}