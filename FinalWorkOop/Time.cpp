#include "Time.h"

static constexpr int SECONDS_IN_DAY = 24 * 3600; // Total seconds in one day

// Constructor: initialize members and validate ranges
Time::Time(int h, int m, int s)
    : hour(h), minute(m), second(s)
{
    validate(); // Ensure values form a valid time
}

// Validate that hour, minute, and second are within their legal ranges
void Time::validate() const {
    if (hour < 0 || hour   > 23) throw std::invalid_argument("Hour 0..23");
    if (minute < 0 || minute > 59) throw std::invalid_argument("Minute 0..59");
    if (second < 0 || second > 59) throw std::invalid_argument("Second 0..59");
}

// Getters for individual components
int Time::getHour()   const { return hour; }
int Time::getMinute() const { return minute; }
int Time::getSecond() const { return second; }

// Setters update component and revalidate
void Time::setHour(int h) { hour = h;   validate(); }
void Time::setMinute(int m) { minute = m; validate(); }
void Time::setSecond(int s) { second = s; validate(); }

// Pre-increment: add one second and return updated object
Time& Time::operator++() { *this += 1; return *this; }

// Post-increment: save current, add one second, return old value
Time  Time::operator++(int) { Time tmp = *this; ++*this; return tmp; }

// Pre-decrement: subtract one second and return updated object
Time& Time::operator--() { *this -= 1; return *this; }

// Post-decrement: save current, subtract one second, return old value
Time  Time::operator--(int) { Time tmp = *this; --*this; return tmp; }

// Add seconds, wrapping around 24-hour boundary
Time Time::operator+(int sec) const {
    int total = ((hour * 3600 + minute * 60 + second) + sec) % SECONDS_IN_DAY;
    if (total < 0) total += SECONDS_IN_DAY; // Wrap negative values into positive range
    int h = total / 3600;
    int m = (total % 3600) / 60;
    int s = total % 60;
    return Time(h, m, s);
}

// Subtraction implemented by adding negative seconds
Time Time::operator-(int sec) const { return *this + (-sec); }

// Compound assignment: add seconds in-place
Time& Time::operator+=(int sec) { return *this = *this + sec; }

// Compound assignment: subtract seconds in-place
Time& Time::operator-=(int sec) { return *this = *this - sec; }

// Comparison operators: compare by total seconds since midnight
bool Time::operator==(const Time& o) const { return hour == o.hour && minute == o.minute && second == o.second; }
bool Time::operator!=(const Time& o) const { return !(*this == o); }
bool Time::operator< (const Time& o) const {
    return (hour * 3600 + minute * 60 + second) < (o.hour * 3600 + o.minute * 60 + o.second);
}
bool Time::operator<=(const Time& o) const { return *this < o || *this == o; }
bool Time::operator> (const Time& o) const { return o < *this; }
bool Time::operator>=(const Time& o) const { return o <= *this; }

// Stream insertion: output in "hh:mm:ss" format with leading zeros
std::ostream& operator<<(std::ostream& os, const Time& t) {
    os
        << (t.hour < 10 ? "0" : "") << t.hour << ':'
        << (t.minute < 10 ? "0" : "") << t.minute << ':'
        << (t.second < 10 ? "0" : "") << t.second;
    return os;
}
