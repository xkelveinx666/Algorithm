#include <cstring>
#include <iostream>
#define k_day 260
using namespace std;

typedef struct {
    int date;
    char month[9];
    int year;
} IO_date;

int main() {
    char habb[][7] = {"pop",  "no",   "zip",   "zotz",  "tzec", "xul", "yoxkin",
                      "mol",  "chen", "yax",   "zac",   "ceh",  "mac", "kankin",
                      "muan", "pax",  "koyab", "cumhu", "uayet"};
    char tzol[][9] = {"imix",  "ik",    "akbal", "kan",   "chicchan",
                      "cimi",  "manik", "lamat", "muluk", "ok",
                      "chuen", "eb",    "ben",   "ix",    "mem",
                      "cib",   "caban", "eznab", "canac", "ahau"};
    IO_date input, output;
    char p;
    int day, i, j;
    int n;
    while (cin >> n) {
        cout << n << endl;
        for (i = 0; i < n; i++) {
            cin >> input.date >> p >> input.month >> input.year;
            j = 0;
            while (strcmp(input.month, habb[j])) j++;
            day = input.year * 365 + j * 20 + input.date;
            output.year = day / k_day;
            strcpy(output.month, tzol[day % 20]);
            output.date = day % 13 + 1;
            cout << output.date << " " << output.month << " " << output.year
                 << endl;
        }
    }
    return 0;
}