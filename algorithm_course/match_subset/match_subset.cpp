#include <iostream>
#include <set>
#include <string>
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
         set<string> *s) {
    if (sum == y) {
        current = current.substr(0, current.length() - 3);
        s->insert(current);
    } else if (index >= 0 && sum < y && sum + array[0] <= y) {
        int newSum = sum;
        string newCurrent = current;
        if (sum + array[index] <= y) {
            newSum += array[index];
            newCurrent += to_string(array[index]);
            newCurrent += " + ";
        }
        dfs(array, index - 1, y, newSum, newCurrent, s);
        dfs(array, index - 1, y, sum, current, s);
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
    set<string> s;
    if (y >= array[0]) {
        dfs(array, length - 1, y, 0, "", &s);
    }
    if (s.size() == 0) {
        cout << "no match set of Y" << endl;
    } else {
        cout << "Y has " << s.size() << " result" << endl;
        set<string>::iterator begin = s.begin();
        set<string>::iterator end = s.end();
        while (begin != end) {
            cout << y << " =  " << *begin << endl;
            begin++;
        }
    }
    return 0;
}
/*
20
1 2 3 4 5 6 7 11 22 q
*/