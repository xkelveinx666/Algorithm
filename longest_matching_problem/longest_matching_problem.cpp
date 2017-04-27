#include <iostream>
#include <string>
#define MAX 100
using namespace std;

int input(int array[]) {
    int value;
    int index = 1;
    cout << "please enter number ,ending when enter zero" << endl;
    while (cin >> value && value != 0) {
        array[index++] = value;
    }
    return index;
}

int matching(int array[], int length) {
    int matchArray[MAX][MAX] = {0};
    int resultMax = array[1];
    int resultIndex = 0;
    int colMax[MAX] = {0};
    for (int row = 1; row < length; row++) {
        int rowMax = array[row];
        for (int col = 1; col <= row; col++) {
            matchArray[row][col] = matchArray[row - 1][col] + array[row];
            if (rowMax < matchArray[row][col]) {
                colMax[row] = col;
                rowMax = matchArray[row][col];
            }
        }
        matchArray[row][0] = rowMax;
        if (resultMax < rowMax) {
            resultIndex = row;
            resultMax = rowMax;
        }
    }
    cout << "the segmetn is ";
    for (int index = colMax[resultIndex]; index <= resultIndex; index++) {
        cout << array[index] << " ";
    }
    cout << endl;
    cout << "result = " << resultMax << endl;
    return resultMax;
}

void output(int array[], int length) {
    for (int index = 1; index < length; index++) {
        cout << array[index] << " ";
    }
    cout << endl;
}

int main(void) {
    int array[MAX] = {0};
    int length = input(array);
    output(array, length);
    matching(array, length);
    return 0;
}