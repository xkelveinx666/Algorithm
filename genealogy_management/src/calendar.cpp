#include <ctime>
#include <iostream>
#define cPointer Calendar*
using namespace std;
class Calendar {
   public:
    bool addCalendar() {
        cout << "输入日期(年、月、日)" << endl;
        int tempYear;
        int tempMonth;
        int tempDay;
        cout << "请输入年份在1949年到2048年之间,支持只输入后两位数" << endl;
        while (cin >> tempYear && tempYear != -1) {
            if ((tempYear >= 1 && tempYear < 100) ||
                (tempYear >= 1949 && tempYear <= 2048)) {
                if ((tempYear >= 1 && tempYear < 100)) {
                    tempYear += tempYear >= 49 ? 1900 : 2000;
                }
                break;
            } else {
                cout << "输入年份必须在1949年到2048年之间,输入-1不设置日期"
                     << endl;
            }
        }
        if (tempYear == -1) {
            this->year = 0;
            this->month = 0;
            this->day = 0;
            return false;
        } else {
            this->year = tempYear;
        }
        cout << "请输入月份,1到12月之间" << endl;
        while (cin >> tempMonth) {
            if (tempMonth >= 1 && tempMonth <= 12) {
                this->month = tempMonth;
                break;
            } else {
                cout << "请输入月份,1到12月之间" << endl;
            }
        }
        cout << "请输入日期,1到31号之间" << endl;
        while (cin >> tempDay) {
            if (tempDay >= 1 && tempDay <= 31) {
                if (judgeLegalDate(tempYear, tempMonth, tempDay)) {
                    this->day = tempDay;
                    break;
                } else {
                    cout << "该日期超过该月最大日期,请重新输入日期" << endl;
                }
            } else {
                cout << "请输入日期,1到31号之间" << endl;
            }
        }
        return true;
    }

    int getYear() { return this->year; }

    int getMonth() { return this->month; }

    int getDay() { return this->day; }

   private:
    int year;
    int month;
    int day;
    bool isLeapYear(int year) {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            return true;
        } else {
            return false;
        }
    }
    bool judgeLegalDate(int year, int month, int day) {
        bool leap = isLeapYear(year);
        int maxDay = 0;
        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                maxDay = 31;
                break;
            case 2:
                maxDay = leap ? 29 : 28;
                break;
            default:
                maxDay = 30;
                break;
        }
        if (day <= maxDay) {
            return true;
        } else {
            return false;
        }
    }
};