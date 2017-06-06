#include <iostream>
#include <set>
#include <string>
using namespace std;
#define MAX 9

void output(int array[], int length) {
    for (int index = 0; index < length; index++) {
        cout << array[index] << " ";
    }
    cout << endl;
}

void calculate(int array[]) {
    double result1 = (double)(array[0] + array[1]) / (array[2]);
    double result2 = (double)(array[3] + array[4]) / (array[5]);
    double result3 = (double)(array[6] + array[7]) / (array[8]);
}

void change(int array[], int left, int right) {
    int temp = array[left];
    array[left] = array[right];
    array[right] = temp;
}

void dfs(int array[], int start, double result1, double result2, double result3,
         int *total) {
    if (start == MAX - 1) {
        if (result1 + result2 == result3) {
            cout << result1 << " + " << result2 << " = " << result3 << "     ";
            output(array, MAX);
            (*total)++;
        }
    } else {
        if (start < 3) {
            result1 = (double)(array[0] / (double)(array[1] * array[2]));
        } else if (start < 6) {
            result2 = (double)(array[3] / (double)(array[4] * array[5]));
        } else {
            result3 = (double)(array[6] / (double)(array[7] * array[8]));
        }
        for (int index = start; index < MAX; index++) {
            /*去掉分母为零或交换无需重新计算的情况*/
            if ((start % 3 == 1 && start + 1 == index) || array[1] == 0 ||
                array[2] == 0 || array[4] == 0 || array[5] == 0 ||
                array[7] == 0 || array[8] == 0) {
                continue;
            }
            change(array, start, index);
            dfs(array, start + 1, result1, result2, result3, total);
            change(array, start, index);
        }
    }
}

void initiate(int array[]) {
    for (int index = 0; index < MAX; index++) {
        array[index] = index + 1;
    }
}
int main(void) {
    int array[MAX];
    initiate(array);
    output(array, MAX);
    int total = 0;
    dfs(array, 0, 0, 0, 0, &total);
    cout << "result = " << total * 2 << endl;
    return 0;
}