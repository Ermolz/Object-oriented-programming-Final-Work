#pragma once

#include <iostream>
#include <stdexcept>

class Time {
public:
    Time(int hour, int minute, int second);

    int getHour()   const;
    int getMinute() const;
    int getSecond() const;

    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);

    Time& operator++();
    Time  operator++(int);
    Time& operator--();
    Time  operator--(int);

    Time  operator+ (int sec) const;
    Time  operator- (int sec) const;
    Time& operator+=(int sec);
    Time& operator-=(int sec);

    bool operator==(const Time& o) const;
    bool operator!=(const Time& o) const;
    bool operator< (const Time& o) const;
    bool operator<=(const Time& o) const;
    bool operator> (const Time& o) const;
    bool operator>=(const Time& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Time& t);

private:
    int hour, minute, second;
    void validate() const;
};
