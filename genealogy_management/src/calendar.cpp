#include <ctime>
#include <iostream>
#define cPointer Calendar *
using namespace std;
class Calendar {
   public:
    bool addCalendar() {
        getCurrentYear();
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
        } else if (tempYear > this->currentYear) {
            cout << "请输入一个小于当前年份的年" << endl;
        } else {
            this->year = tempYear;
        }
        cout << "请输入月份,1到12月之间" << endl;
        while (cin >> tempMonth) {
            if (tempMonth >= 1 && tempMonth <= 12) {
                if (tempMonth > this->currentMonth) {
                    cout << "请输入一个小于当前月份的月" << endl;
                } else {
                    this->month = tempMonth;
                    break;
                }
            } else {
                cout << "请输入月份,1到12月之间" << endl;
            }
        }
        cout << "请输入日期,1到31号之间" << endl;
        while (cin >> tempDay) {
            if (tempDay >= 1 && tempDay <= 31) {
                if (judgeLegalDate(tempYear, tempMonth, tempDay)) {
                    if (tempDay > this->currentDay) {
                        cout << "请输入一个小于当前日期的日" << endl;
                    } else {
                        this->day = tempDay;
                        break;
                    }
                } else {
                    cout << "该日期超过该月最大日期,请重新输入日期" << endl;
                }
            } else {
                cout << "请输入日期,1到31号之间" << endl;
            }
        }
        return true;
    }

    int compareCalendar(cPointer otherCalendar) {
        return this->getYear() > otherCalendar->getYear()
                   ? 1
                   : this->getMonth() > otherCalendar->getMonth()
                         ? 1
                         : this->getDay() > otherCalendar->getDay();
    }

    int getYear() { return this->year; }

    int getMonth() { return this->month; }

    int getDay() { return this->day; }

    bool setCalendar(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
        return year;
    }

   private:
    int year;
    int month;
    int day;
    int currentYear;
    int currentMonth;
    int currentDay;
    void getCurrentYear() {
        time_t now_time;
        now_time = time(NULL);
        tm *currentTime = localtime(&now_time);
        this->year = currentTime->tm_year + 1900;
        this->month = currentTime->tm_mon + 1;
        this->day = currentTime->tm_mday;
    }
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