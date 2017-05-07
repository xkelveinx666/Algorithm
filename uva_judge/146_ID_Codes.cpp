#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int main(void) {
    string str;
    while (cin >> str) {
        if (str[0] == '#') {
            break;
        }
        if (next_permutation(str.begin(), str.end())) {
            cout << str.c_str() << endl;
        } else {
            cout << "No Successor" << endl;
        }
    }
    return 0;
}
/*
abaacb
cbbaa
#
*/