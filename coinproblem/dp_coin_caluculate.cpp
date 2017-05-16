#include <algorithm>
#include <iostream>
using namespace std;
#define MAX 1000

void dpCalculateCoin(double coins[], int cLength, double coin) {
    double resultArray[MAX][MAX];
    int rLength = coin / coins[0];
    //行代表数值的所有可能个数，列表示所有硬币面值，每一格表示当前面值需要几次
    resultArray[0][0] = 0;
    // lastIndex保存每一次找零最好的情况的面值
    int lastIndex[MAX];
    // value记录所有数值
    double value[MAX];
    for (int row = 1; row <= rLength; row++) {
        resultArray[row][0] = row;
        value[row] = coins[0] * resultArray[row][0];
        double currentSum = value[row];
        for (int col = 1; col < cLength; col++) {
            double sum = coins[col] * (resultArray[row - 1][col] + 1);
            if (sum <= currentSum) {
                resultArray[row][col] = resultArray[row - 1][col] + 1;
            } else {
                resultArray[row][col] = resultArray[row - 1][col];
            }
            if (resultArray[row][col] != 0) {
                lastIndex[row] = col;
            }
        }
    }
    double sum = value[rLength];
    int index = rLength;
    cout << "result = ";
    while (sum != 0) {
        int times = resultArray[index][lastIndex[index]];
        while (times-- > 0) {
            sum -= coins[lastIndex[index]];
            cout << coins[lastIndex[index]] << " ";
        }
        for (int row = 0; row <= rLength; row++) {
            if (value[row] == sum) {
                index = row;
                break;
            }
        }
        if (sum < 0 || index == rLength) {
            cout << endl;
            cout << "无法找零" << endl;
            break;
        }
    }
    cout << endl;
    //输出数组信息
    // for (int row = 0; row <= rLength; row++) {
    //     for (int col = 0; col < cLength; col++) {
    //         cout << resultArray[row][col] << "      ";
    //     }
    //     cout << endl;
    // }
    // for (int row = 0; row <= rLength; row++) {
    //     cout << lastIndex[row] << " ";
    // }
    // cout << endl;
    // for (int row = 0; row <= rLength; row++) {
    //     cout << value[row] << " ";
    // }
    // cout << endl;
}

int main(void) {
    int n;
    int m;
    double coins[MAX];
    double coin;
    int cLength = 0;
    cout << "enter loose money, less than zero to quit" << endl;
    while (cin >> coin && coin > 0) {
        coins[cLength++] = coin;
    }
    cout << "enter coin" << endl;
    cin >> coin;
    sort(coins, coins + cLength);
    dpCalculateCoin(coins, cLength, coin);
    return 0;
}

/*
sample input
0.5 68.29 1 2 3 4.5 6 17 12 36  45 -1
261.5
*/