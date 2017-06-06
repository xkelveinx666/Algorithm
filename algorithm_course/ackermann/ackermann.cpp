#include <iostream>
using namespace std;
#define MAX 1000

long ackermann(long m, long n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

long dpAckermann(long m, long n) {
    long array[MAX] = {0};
    if (m <= 2) {
        array[0] = m + 1;
        for (int i = 1; i <= m; i++) {
            array[i] = array[i - 1] + n;
        }
        return array[m];
    } else {
        array[0] = m + 2;
        for (int i = 1; i <= n; i++) {
            array[i] = (array[i - 1] * 2) + m;
        }
        return array[n];
    }
}

int main(void) {
    int n;
    int m;
    cout << "enter m and n" << endl;
    cin >> m >> n;
    cout << "result = " << ackermann(m, n) << endl;
    cout << "result = " << dpAckermann(m, n) << endl;
    return 0;
}