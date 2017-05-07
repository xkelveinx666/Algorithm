#include <algorithm>
#include <iostream>
#define N 101
using namespace std;
int main(void) {
    int array[N][N] = {0};
    int n;
    while (cin >> n) {
        int sum = -127;
        for (int i = 1; i <= n; i++) {
            for (int j = 1, k = 1; j <= n && k <= n; j++, k++) {
                cin >> array[i][j];
                if (array[i][j] > sum) {
                    sum = array[i][j];
                }
            }
        }
    }
    return 0;
}
/*
4
0  -2  -7    0  9    2  -6    2
-4    1  -4    1  -1
8    0  -2
*/