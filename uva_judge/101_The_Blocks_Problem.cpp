#include <iostream>
#include <string>
#define N 25
using namespace std;
void move(int array[][N], int position[], int a, int b, int type) {
    int pa = a - '0';
    int pb = b - '0';
    int aIndex = 0;
    int bIndex = 0;
    if (position[pa] == position[pb]) {
        return;
    }
    while (array[position[pa]][aIndex] != a) {
        aIndex++;
    }
    while (array[position[pb]][bIndex] != b) {
        bIndex++;
    }
    int bLength = bIndex;
    while (array[position[pb]][bLength] != 0) {
        bLength++;
    }
    if (type == 0) {
        while (bLength != bIndex + 1) {
            array[position[pb]][bLength] = array[position[pb]][bLength - 1];
            bLength--;
        }
        array[position[pb]][bIndex + 1] = array[position[pa]][aIndex];
    } else {
        array[position[pb]][bLength] = array[position[pa]][aIndex];
    }
    array[position[pa]][aIndex] = 0;
    position[pa] = position[pb];
}
void pile(int array[][N], int position[], int a, int b, int type) {
    int pa = a - '0';
    int pb = b - '0';
    int aIndex = 0;
    int bIndex = 0;
    if (position[pa] == position[pb]) {
        return;
    }
    while (array[position[pa]][aIndex] != a) {
        aIndex++;
    }
    while (array[position[pb]][bIndex] != b) {
        bIndex++;
    }
    int bLength = bIndex;
    while (array[position[pb]][bLength] != 0) {
        bLength++;
    }
    int aLength = aIndex;
    while (array[position[pa]][aLength] != 0) {
        aLength++;
    }
    if (type == 0) {
        int tempAIndex = aIndex;
        while (tempAIndex != aLength) {
            array[position[pb]][bLength++] = array[position[pa]][tempAIndex++];
        }
        while (aIndex < tempAIndex) {
            int tempA = array[position[pa]][--tempAIndex] - '0';
            array[position[pa]][tempAIndex] = 0;
            position[tempA] = position[pb];
        }
    } else {
        int newbLength = bLength + aLength - aIndex - bIndex - 3;
        int newALength = aLength - aIndex - 2;
        while (newbLength > bLength) {
            array[position[pb]][newbLength + newALength] =
                array[position[pb]][newbLength];
            newbLength--;
        }
        int tempAIndex = aIndex;
        while (array[position[pa]][tempAIndex] != 0) {
            array[position[pb]][bLength++] = array[position[pa]][tempAIndex++];
        }
        while (aIndex < tempAIndex) {
            int tempA = array[position[pa]][--tempAIndex] - '0';
            array[position[pa]][tempAIndex] = 0;
            position[tempA] = position[pb];
        }
    }
}
void outputPoi(int position[], int n) {
    for (int i = 0; i < n; i++) {
        cout << i << ":" << position[i] << " " << endl;
    }
}
void output(int array[][N], int n) {
    for (int i = 0; i < n; i++) {
        cout << i << ":";
        int j = 0;
        while (array[i][j] != 0) {
            cout << " " << (array[i][j++] - '0');
        }
        cout << endl;
    }
}
int main(void) {
    int n;
    cin >> n;
    string instruction1;
    string instruction2;
    int blocksLeft;
    int blocksRight;
    int array[N][N] = {0};
    int position[N] = {0};
    int type = 0;
    for (int i = 0; i < n; i++) {
        array[i][0] = i + '0';
        position[i] = i;
    }
    while (true) {
        cin >> instruction1;
        if (instruction1 == "quit") {
            break;
        } else if (instruction1 != "move" && instruction1 != "pile") {
            continue;
        }
        cin >> blocksLeft;
        cin >> instruction2;
        if (instruction2 == "onto") {
            type = 0;
        } else if (instruction2 == "over") {
            type = 1;
        } else {
            continue;
        }
        cin >> blocksRight;
        if (blocksLeft == blocksRight) {
            continue;
        }
        blocksLeft += '0';
        blocksRight += '0';
        if (instruction1 == "move") {
            move(array, position, blocksLeft, blocksRight, type);
        } else {
            pile(array, position, blocksLeft, blocksRight, type);
        }
        outputPoi(position, n);
        output(array, n);
    }
    output(array, n);
    return 0;
}
/*
10
move 9 onto 1
move 8 over 1
pile 9 onto 3
*/