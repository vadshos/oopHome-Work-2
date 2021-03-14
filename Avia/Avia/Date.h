#pragma once
#include <iostream>
#include <string>

class Date {
public:
    Date(int d = 0, int m = 0, int y = 0) {
        setDate(d, m, y);
    }

    Date(const Date& date) {
        setDate(date.day, date.month, date.year);
    }

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    void setDay(int day) {
        this->day = day;
    }

    void setMonth(int month) {
        this->month = month;
    }

    void setYear(int year) {
        this->year = year;
    }

    void setDate(int day, int month, int year) {
        if (isValidDate(day, month, year)) {
            setDay(day);
            setMonth(month);
            setYear(year);
        }
        else {
            throw std::string("Not valid date");
        }
    }

    void print() const {
        std::cout << day << '/'
            << month << '/'
            << year << std::endl;
    }

    static bool isValidDate(int day, int month, int year) {
        // Здесь необходимо описать процедуру проверки даты на корректность
        return true;
    }

    static bool isLeapYear(int year) {
        // Здесь необходимо проверить является ли год високосным
        return false;
    }

    static int dayInMonth(int month) {
        // Здесь определить количество дней в месяце
        return 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        os << obj.day << '/'
            << obj.month << '/'
            << obj.year;
        return os;
    }
private:
    int day;
    int month;
    int year;
};