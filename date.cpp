#include "date.h"
#include <iostream>
#include <string>

Date::Date() {
    setDate(1, 1, 1970);
}

Date::Date(int d = 1, int m = 1, int y = 1970) {
    setDate(d, m, y);
}
Date::Date(const Date& date) {
    setDate(date.day, date.month, date.year);
}
int Date::getDay() const {
    return day;
}
int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(int day) {
    this->day = day;
}

void Date::setMonth(int month) {
    this->month = month;
}

void Date::setYear(int year) {
    this->year = year;
}

void Date::setDate(int day, int month, int year) {
    if (isValidDate(day, month, year)) {
        setDay(day);
        setMonth(month);
        setYear(year);
    }
    else {
        throw std::string("Not valid date");
    }
}

std::string Date::getDate(){
    std::string str = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    return str;
}

bool Date::isValidDate(int day, int month, int year) {
    return ((day > 0 && day <= dayInMonth(month, year)) && (month > 0 && month <= 12));
}

bool Date::isLeapYear(int year) { 
    return (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0));
}

int Date::dayInMonth(int month, int year) {
    switch (month)
    {
    case 1:
        return 31;
    case 2:
        return 28 + isLeapYear(year);
    case 3:
        return 31;
    case 4:
        return 30;
    case 5:
        return 31;
    case 6:
        return 30;
    case 7:
        return 31;
    case 8:
        return 31;
    case 9:
        return 30;
    case 10:
        return 31;
    case 11:
        return 30;
    case 12:
        return 31;
    default:
        return -1;
        break;
    }
}
