#include <iostream>
#define TYPE 3
#define N 5000
using namespace std;
void showRestArray(int restArray[]) {
    cout << "Array" << endl;
    cout << "a : " << restArray[0] << endl;
    cout << "b : " << restArray[1] << endl;
    cout << "c : " << restArray[2] << endl;
}
void pullChar(char aliceArray[], int bobRestArray[], int aliceRestArray[],
              int n) {
    char resultArray[N];
    int bobOtherArray[TYPE] = {0};
    bobOtherArray[0] =
        aliceRestArray[1] + aliceRestArray[2] - aliceRestArray[0];
    bobOtherArray[1] =
        aliceRestArray[0] + aliceRestArray[2] - aliceRestArray[1];
    bobOtherArray[2] =
        aliceRestArray[0] + aliceRestArray[1] - aliceRestArray[2];
    showRestArray(bobOtherArray);
    for (int i = 0; i < n; i++) {
        char current;
        switch (aliceArray[i]) {
            case 'a':
                current =
                    bobOtherArray[2] >= 0 && bobRestArray[1] > 0 ? 'b' : 'c';
                if (current == 'b') {
                    bobOtherArray[2]--;
                } else {
                    bobOtherArray[1]--;
                }
                break;
            case 'b':
                current =
                    bobOtherArray[2] >= 0 && bobRestArray[0] > 0 ? 'a' : 'c';
                if (current == 'a') {
                    bobOtherArray[2]--;
                } else {
                    bobOtherArray[0]--;
                }
                break;
            case 'c':
                current =
                    bobOtherArray[1] >= 0 && bobRestArray[0] > 0 ? 'a' : 'b';
                if (current == 'a') {
                    bobOtherArray[1]--;
                } else {
                    bobOtherArray[0]--;
                }
                break;
        }
        bobRestArray[current - 'a']--;
        // showRestArray(bobRestArray);
        resultArray[i] = current;
    }
    cout << "reult = " << resultArray << endl;
}
int main(void) {
    int n;
    int t;
    cin >> t;
    while (t-- > 0) {
        cin >> n;
        int tempN = n;
        char bobArray[N];
        char aliceArray[N];
        char resultArray[N];
        int bobRestArray[TYPE] = {0};
        int aliceRestArray[TYPE] = {0};
        for (int i = 0; i < n; i++) {
            char ch;
            cin >> ch;
            bobArray[i] = ch;
            bobRestArray[ch - 'a']++;
        }
        bobArray[n] = '\0';
        for (int i = 0; i < n; i++) {
            char ch;
            cin >> ch;
            aliceArray[i] = ch;
            aliceRestArray[ch - 'a']++;
        }
        aliceArray[n] = '\0';
        pullChar(aliceArray, bobRestArray, aliceRestArray, n);
    }
    return 0;
}