#include <iostream>
#include <string>
using namespace std;
#define MAX 6
int main(void) {
    string possible[] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};
    long n[3][3];
    int sum[MAX];
    while (cin >> n[0][0] >> n[0][1] >> n[0][2] >> n[1][0] >> n[1][1] >>
           n[1][2] >> n[2][0] >> n[2][1] >> n[2][2]) {
        sum[0] = n[1][0] + n[2][0] + n[0][2] + n[2][2] + n[0][1] + n[1][1];
        sum[1] = n[1][0] + n[2][0] + n[0][1] + n[2][1] + n[0][2] + n[1][2];
        sum[2] = n[1][2] + n[2][2] + n[0][0] + n[2][0] + n[0][1] + n[1][1];
        sum[3] = n[1][2] + n[2][2] + n[0][1] + n[2][1] + n[0][0] + n[1][0];
        sum[4] = n[1][1] + n[2][1] + n[0][0] + n[2][0] + n[0][2] + n[1][2];
        sum[5] = n[1][1] + n[2][1] + n[0][2] + n[2][2] + n[0][0] + n[1][0];
        int min = sum[0];
        int minIndex = 0;
        for (int i = 1; i < MAX; i++) {
            if (sum[i] < min) {
                min = sum[i];
                minIndex = i;
            }
        }
        cout << possible[minIndex] << " " << min;
    }

    return 0;
}
/*
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
*/