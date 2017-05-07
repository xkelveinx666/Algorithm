#include <iostream>
using namespace std;
int algorithm(long long n) {
    int times = 1;
    while (n != 1) {
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        times++;
    }
    return times;
}
int getMaxCycleLength(int i, int j) {
    int temp;
    int max = 0;
    if (i > j) {
        temp = i;
        i = j;
        j = temp;
    }
    for (; i <= j; i++) {
        int result = algorithm(i);
        max = max < result ? result : max;
    }
    return max;
}
int main(void) {
    int i, j;
    while (cin >> i >> j) {
        cout << i << " " << j << " " << getMaxCycleLength(i, j) << endl;
    }
    return 0;
}