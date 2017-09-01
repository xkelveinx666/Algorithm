#include <cstring>
#include <iostream>
using namespace std;
#define BLOCKS_NUMBER 3
//显示数组
void showArray(int array[]) {
    for (int index = 0; index < BLOCKS_NUMBER; index++) {
        cout << array[index];
    }
    cout << endl;
}
//判断数据是否已经存在
bool exist(int array[], int page) {
    for (int index = 0; array[index] != 0; index++) {
        if (array[index] == page) {
            return true;
        }
    }
    return false;
}
//将数据插入到数组中，模拟链表
int push(int inputArray[], int x) {
    int index = 0;
    for (; inputArray[index] != 0; index++) {
    }
    inputArray[index] = x;
    return index;
}
//找出最近最久未使用的数字的下标
int getValueIndex(int array[], int length, int blocks[]) {
    int judgeArray[BLOCKS_NUMBER + 1] = {0};
    int jaLength = 0;
    int index;
    for (index = length; index >= 0 && jaLength != 3; index--) {
        if (!exist(judgeArray, array[index])) {
            jaLength = push(judgeArray, array[index]);
        }
    }
    int x = judgeArray[jaLength];
    for (index = 0; index < BLOCKS_NUMBER; index++) {
        if (blocks[index] == x) {
            return index;
        }
    }
    return -1;
}

int main(void) {
    int blocks[BLOCKS_NUMBER] = {0};
    int inputArray[BLOCKS_NUMBER * BLOCKS_NUMBER * BLOCKS_NUMBER *
                   BLOCKS_NUMBER] = {0};
    int index = -1;
    int page;
    int length = 0;
    int errorCount = 0;
    int totalCount = 0;
    while (cin >> page && page != 0) {
        totalCount++;
        length = push(inputArray, page);
        cout << "page  =   " << page << "   ";
        if (length == -1) {
            break;
        }
        if (!exist(blocks, page)) {
            if (length > 2) {
                index = getValueIndex(inputArray, length, blocks);
            } else {
                index++;
            }
            if (blocks[index] != page) {
                errorCount++;
                blocks[index] = page;
            }
            showArray(blocks);
        } else {
            cout << endl;
        }
    }
    cout << "count of lost page " << errorCount << endl;
    cout << "ratio of lost page " << (double)errorCount / totalCount << endl;
    return 0;
}

// 1 4 2 5 3 3 2 4 2 5 6 0