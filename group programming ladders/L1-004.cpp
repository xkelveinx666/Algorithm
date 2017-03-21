#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstring>
using namespace std;
double computeCelsius(double fahrenheit) {
    double celsius;
    celsius = 5*(fahrenheit - 32)/9;
    cout<<"Celsius = "<<(int)celsius<<endl;
    return celsius;
}
int main(void) {
    double fahrenheit;
    cin>>fahrenheit;
    computeCelsius(fahrenheit);
    return 0;
}