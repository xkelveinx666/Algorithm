#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MAX 100
int input(int array[]) {
    int x, length = 0;
    cout << "enter number of X,end with 'q' " << endl;
    while (cin >> x && x != 'q') {
        array[length++] = x;
    }
    return length;
}
void output(int array[], int length) {
    for (int index = 0; index < length; index++) {
        cout << array[index] << " ";
    }
    cout << endl;
}

void dfs(int array[], int index, int y, int sum, string current,
         vector<string> *vec) {
    if (sum == y) {
        vec->push_back(current);
        cout << current << endl;
    } else if (sum < y) {
        if (sum + array[index] <= y) {
            sum += array[index];
            current += array[index];
            current += " + ";
        }
        dfs(array, index - 1, y, sum, current, vec);
    }
}

int main(void) {
    int y;
    cout << "enter y" << endl;
    cin >> y;
    int array[MAX];
    int length = input(array);
    cout << "the array is" << endl;
    output(array, length);
    sort(array, array + length);
    vector<string> vec(length);
    dfs(array, length - 1, y, 0, "", &vec);
    if (vec.size() == 0) {
        cout << "no match set of Y" << endl;
    } else {
        cout << "Y has " << endl;
        vector<string>::iterator begin = vec.begin();
        vector<string>::iterator end = vec.end();
        while (begin != end) {
            cout << *begin << endl;
            begin++;
        }
    }
    return 0;
}
/*
20
1 2 3 4 5 6 7 11 22 q
*/