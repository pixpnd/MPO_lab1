#pragma once
#include <string>
class Date {
public:
    Date();
    Date(int d, int m, int y);

    Date(const Date& date);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    void setDay(int day);

    void setMonth(int month);

    void setYear(int year);

    void setDate(int day, int month, int year);
    std::string getDate();
    static bool isValidDate(int day, int month, int year);

    static bool isLeapYear(int year);
    static int dayInMonth(int month, int year);

    bool operator < (const Date& d2) {
        if (this->getYear() < d2.getYear()) {
            return true;
        }
        else {
            if (this->getMonth() < d2.getMonth()) {
                return true;
            }
            else {
                if (this->getDay() < d2.getDay()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    bool operator > (const Date& d2) {
        if (this->getYear() > d2.getYear()) {
            return true;
        }
        else {
            if (this->getMonth() > d2.getMonth()) {
                return true;
            }
            else {
                if (this->getDay() > d2.getDay()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    bool isLess (const Date& d2) {
        if (this->getYear() < d2.getYear()) {
            return true;
        }
        else {
            if (this->getMonth() < d2.getMonth()) {
                return true;
            }
            else {
                if (this->getDay() < d2.getDay()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    bool isMore (const Date& d2) {
        if (this->getYear() > d2.getYear()) {
            return true;
        }
        else {
            if (this->getMonth() > d2.getMonth()) {
                return true;
            }
            else {
                if (this->getDay() > d2.getDay()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }

private:
    int day;
    int month;
    int year;
};