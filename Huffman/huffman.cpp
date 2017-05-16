#include <cstring>
#include <iostream>
using namespace std;
#define MAX 100
#define pointer struct node *
struct node {
    char character;
    double ratio;
    int leftChild;
    int rightChild;
    int father;
    bool deal;
};
int input(pointer nodes[MAX], int *maxIndex) {
    char ch;
    double r;
    int length = 0;
    cout << "输入字符和对应的比例，字符为q退出" << endl;
    double max = -1;
    while (cin >> ch && ch != 'q') {
        cin >> r;
        pointer p = new node;
        p->character = ch;
        p->ratio = r;
        if (r > max) {
            max = r;
            *maxIndex = length;
        }
        p->leftChild = -1;
        p->rightChild = -1;
        p->father = -1;
        p->deal = false;
        nodes[length++] = p;
    }
    return length;
}
void findTheLeast(pointer nodes[MAX], int length, int *minIndex1,
                  int *minIndex2) {
    for (int index = 0; index < length; index++) {
        if (nodes[index]->deal) {
            continue;
        }
        if (nodes[index]->ratio <= nodes[*minIndex1]->ratio) {
            if (*minIndex1 != 0) {
                *minIndex2 = *minIndex1;
            }
            if (nodes[index]->ratio == nodes[*minIndex1]->ratio &&
                nodes[index]->ratio < nodes[*minIndex2]->ratio) {
                *minIndex2 = index;
            } else {
                *minIndex1 = index;
            }
        } else if (nodes[index]->ratio < nodes[*minIndex2]->ratio) {
            *minIndex2 = index;
        }
    }
    if (nodes[*minIndex1]->ratio == nodes[*minIndex2]->ratio &&
        *minIndex1 > *minIndex2) {
        int temp = *minIndex1;
        *minIndex1 = *minIndex2;
        *minIndex2 = temp;
    }
}

void showResult(pointer nodes[MAX], int length) {
    for (int index = 0; index < length; index++) {
        cout << "index = " << index << "   ";
        cout << "char = " << nodes[index]->character << "   ";
        cout << "ratio = " << nodes[index]->ratio << "   ";
        cout << "father = " << nodes[index]->father << "   ";
        cout << "lChild = " << nodes[index]->leftChild << "   ";
        cout << "rChild = " << nodes[index]->rightChild << "   ";
        cout << "deal = " << nodes[index]->deal << "   " << endl;
    }
}

void showCode(pointer nodes[MAX], int index, char path[MAX], int length) {
    if (nodes[index]->leftChild == -1 && nodes[index]->rightChild == -1) {
        cout << nodes[index]->character << ":";
        cout << path << endl;
        path[length - 1] = '\0';
        return;
    }
    if (nodes[index]->leftChild != -1) {
        path[length] = '0';
        path[length + 1] = '\0';
        showCode(nodes, nodes[index]->leftChild, path, length + 1);
    }
    if (nodes[index]->rightChild != -1) {
        path[length] = '1';
        path[length + 1] = '\0';
        showCode(nodes, nodes[index]->rightChild, path, length + 1);
    }
}

bool end(pointer nodes[MAX], int length) {
    for (int index = 0; index < length; index++) {
        if (!(nodes[index]->deal)) {
            return false;
        }
    }
    return true;
}
int createHuffman(pointer nodes[MAX], int length, int maxIndex) {
    int originalLength = length;
    for (int index = 0; index < originalLength; index++) {
        double max = nodes[maxIndex]->ratio;
        int minIndex1 = maxIndex, minIndex2 = maxIndex;
        findTheLeast(nodes, length, &minIndex1, &minIndex2);
        if (minIndex1 == minIndex2) {
            nodes[length - 1]->father = -1;
            continue;
        }
        pointer p = new node;
        nodes[length] = p;
        nodes[minIndex1]->deal = true;
        nodes[minIndex2]->deal = true;
        p->ratio = nodes[minIndex1]->ratio + nodes[minIndex2]->ratio;
        if (p->ratio >= max) {
            maxIndex = length;
        }
        nodes[minIndex1]->father = length;
        nodes[minIndex2]->father = length;
        p->leftChild = minIndex1;
        p->rightChild = minIndex2;
        length++;
    }
    return length;
}

int main(void) {
    pointer nodes[MAX];
    int maxIndex;
    int length = input(nodes, &maxIndex);
    int newLength = createHuffman(nodes, length, maxIndex);
    showResult(nodes, newLength);
    char path[MAX];
    showCode(nodes, newLength - 1, path, 0);
    return 0;
}
// a 0.6 b 0.4 c 0.2 y 0.5
// a 5 b 15 c 40 d 30 e 10 q