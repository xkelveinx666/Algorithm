#include <cmath>
#include <iostream>
using namespace std;
#define MAX 10

int shortestLength;
string path;

int getLength(int circuitArray[MAX][MAX], int rI, int rJ, int lI, int lJ) {
    return fabs(lJ - rJ) + fabs(lI - rI) - 1;
}

void dfs(int circuitArray[MAX][MAX], int cI, int cJ, string sPath, int eI,
         int eJ) {
    sPath.append(" -> (" + to_string(cI) + "," + to_string(cJ) + ")");
    cout << sPath << endl;
    if (cI < 0 || cJ < 0) {
        return;
    }
    if (cI == eI && cJ == eJ) {
        path = sPath;
        return;
    }
    if (circuitArray[cI - 1][cJ] == 0 &&
        getLength(cI - 1, cJ, eI, eJ) < shortestLength) {
        shortestLength = getLength(cI - 1, cJ, eI, eJ);
        dfs(circuitArray, cI - 1, cJ, sPath, eI, eJ);
    }
    if (circuitArray[cI][cJ - 1] == 0 &&
        getLength(cI, cJ - 1, eI, eJ) < shortestLength) {
        shortestLength = getLength(cI, cJ - 1, eI, eJ);
        dfs(circuitArray, cI, cJ - 1, sPath, eI, eJ);
    }
    if (circuitArray[cI + 1][cJ] == 0 &&
        getLength(cI + 1, cJ, eI, eJ) < shortestLength) {
        shortestLength = getLength(cI + 1, cJ, eI, eJ);
        dfs(circuitArray, cI + 1, cJ, sPath, eI, eJ);
    }
    if (circuitArray[cI][cJ + 1] == 0 &&
        getLength(cI, cJ + 1, eI, eJ) < shortestLength) {
        shortestLength = getLength(cI, cJ + 1, eI, eJ);
        dfs(circuitArray, cI, cJ + 1, sPath, eI, eJ);
    }
}

int main(void) {
    int circuitArray[MAX][MAX];
    int row;
    int col;
    cin >> row >> col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            circuitArray[i][j] = 0;
        }
    }
    int nI, nJ;
    while (cin >> nI && nI != -1 && cin >> nJ && nJ != -1) {
        circuitArray[nI][nJ] = 1;
    }
    int sI, sJ;
    int eI, eJ;
    cin >> sI >> sJ >> eI >> eJ;
    circuitArray[eI][eJ] = 2;
    shortestLength = getLength(sI, sJ, eI, eJ);
    string sPath;
    dfs(circuitArray, sI, sJ, sPath, eI, eJ);
    cout << shortestLength << endl;
    cout << path << endl;
    return 0;
}

/*
7 7
2 0 2 1 3 1 4 2 3 3 4 3 0 4 4 4 0 5 1 5 2 5 0 6 1 6 2 6  -1
1 2 5 3
*/