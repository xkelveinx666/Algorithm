#include <iostream>
using namespace std;
#define H 101
#define W 101
void dfs(char array[H][W], int i, int j, int h, int w, bool *flag) {
    if (i > h || j > w || array[i][j] == '.') {
        return;
    }
    if (array[i][j] == '#') {
        *flag = true;
        array[i][j] = '.';
        if (array[i][j + 1] == '#') {
            dfs(array, i, j + 1, h, w, flag);
        }
        if (array[i + 1][j] == '#') {
            dfs(array, i + 1, j, h, w, flag);
        }
        if (array[i - 1][j] == '#') {
            dfs(array, i - 1, j, h, w, flag);
        }
        if (array[i][j - 1] == '#') {
            dfs(array, i, j - 1, h, w, flag);
        }
    }
}
int main(void) {
    int t, h, w;
    while (cin >> t) {
        while (t-- > 0) {
            char array[H][W];
            cin >> h >> w;
            for (int i = 1; i <= h; i++) {
                for (int j = 1; j <= w; j++) {
                    cin >> array[i][j];
                }
            }
            int sum = 0;
            for (int i = 1; i <= h; i++) {
                for (int j = 1; j <= w; j++) {
                    bool flag = false;
                    dfs(array, i, j, h, w, &flag);
                    if (flag == true) {
                        sum++;
                    }
                }
            }
            cout << sum << endl;
        }
    }
    return 0;
}