#include "Date.h"

// --- Helper functions for month lengths and leap years ---
static bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Days per month: index 1=January..12=December
static int daysInMonth(int y, int m) {
    static const int dim[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) return 29;
    return dim[m];
}

// Constructor: initialize year, month, day and enforce invariants
Date::Date(int y, int m, int d)
    : year(y), month(m), day(d)
{
    validate(); // Ensure date is valid
}

// Validate date fields: year>=1, month in 1..12, day within month's range
void Date::validate() const {
    if (year < 1)       throw std::invalid_argument("Year must be >= 1");
    if (month < 1 || month>12) throw std::invalid_argument("Month 1..12");
    if (day < 1 || day > daysInMonth(year, month))
        throw std::invalid_argument("Invalid day for given month/year");
}

// Getters for year, month, day components\int Date::getYear()  const { return year; }
int Date::getYear()  const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay()   const { return day; }

// Setters update component and revalidate the dateoid Date::setYear(int y) { year = y;     validate(); }
void Date::setYear(int y) { year = y; validate(); }
void Date::setMonth(int m) { month = m; validate(); }
void Date::setDay(int d) { day = d; validate(); }

// Calculate day of week using Zeller's congruence for Gregorian calendar
// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
int Date::dayOfWeek() const {
    int y = year, m = month, d = day;
    if (m < 3) { m += 12; --y; }
    int K = y % 100, J = y / 100;
    // h: 0=Saturday,1=Sunday,...6=Friday
    int h = (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    // Convert h to 0=Sunday..6=Saturday
    return (h + 6) % 7;
}

// Convert this date to its Julian Day Number
long Date::toJDN() const {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    // Standard formula for Gregorian dates
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

// Static: convert a JDN back into a Date (inverse of toJDN)
Date Date::fromJDN(long jdn) {
    long a = jdn + 32044;
    long b = (4 * a + 3) / 146097;
    long c = a - (146097 * b) / 4;
    long d = (4 * c + 3) / 1461;
    long e = c - 1461 * d / 4;
    long m = (5 * e + 2) / 153;
    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + m / 10;
    return Date(year, month, day);
}

// Pre-increment: add one day to this date
Date& Date::operator++() { *this += 1; return *this; }
// Post-increment: return old date, then add one day
Date  Date::operator++(int) { Date tmp = *this; ++*this; return tmp; }
// Pre-decrement: subtract one day from this date
Date& Date::operator--() { *this -= 1; return *this; }
// Post-decrement: return old date, then subtract one day
Date  Date::operator--(int) { Date tmp = *this; --*this; return tmp; }

// Add n days by converting to JDN and back
Date Date::operator+ (int n) const { return fromJDN(toJDN() + n); }
// Subtract n days similarly
Date Date::operator- (int n) const { return fromJDN(toJDN() - n); }
// Compound assignment for adding days
Date& Date::operator+=(int n) { *this = *this + n; return *this; }
// Compound assignment for subtracting days
Date& Date::operator-=(int n) { *this = *this - n; return *this; }

// Equality: dates equal if JDNs match
bool Date::operator==(const Date& o) const { return toJDN() == o.toJDN(); }
// Inequality
bool Date::operator!=(const Date& o) const { return !(*this == o); }
// Less-than by chronological order (JDN comparison)
bool Date::operator< (const Date& o) const { return toJDN() < o.toJDN(); }
// Other comparison operators
bool Date::operator<=(const Date& o) const { return toJDN() <= o.toJDN(); }
bool Date::operator> (const Date& o) const { return o < *this; }
bool Date::operator>=(const Date& o) const { return o <= *this; }

// Output date in yyyy-mm-dd format with leading zeros
std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.year << '-'
        << (d.month < 10 ? "0" : "") << d.month << '-'
        << (d.day < 10 ? "0" : "") << d.day;
    return os;
}