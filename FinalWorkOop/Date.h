#pragma once

#include <iostream>
#include <stdexcept>

class Date {
public:
    Date(int year, int month, int day);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);

    int dayOfWeek() const;

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    Date  operator+ (int days) const;
    Date  operator- (int days) const;
    Date& operator+=(int days);
    Date& operator-=(int days);

    bool operator==(const Date& o) const;
    bool operator!=(const Date& o) const;
    bool operator< (const Date& o) const;
    bool operator<=(const Date& o) const;
    bool operator> (const Date& o) const;
    bool operator>=(const Date& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Date& d);

private:
    int year;
    int month;
    int day;

    void validate() const;
    long toJDN() const;
    static Date fromJDN(long jdn);
};