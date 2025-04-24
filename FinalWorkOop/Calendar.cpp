#include "Calendar.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

//  Helper functions for month lengths and leap years 
static bool isLeap(int y) {
    // Return true if year y is a leap year in the Gregorian calendar
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
static int daysInMonth(int y, int m) {
    // Number of days for each month (1-based), February adjusted for leap years
    static const int dim[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) return 29;
    return dim[m];
}

//  Static helper to obtain today's date without relying on Date default constructor 
Date Calendar::getToday() {
    using namespace std::chrono;
    // Get current time as time_t
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    std::tm tm{};
    // Convert to local time (MSVC safe version)
    localtime_s(&tm, &tt);
    // Construct a Date object for today
    return Date(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// Constructor: initialize to today's month and year
Calendar::Calendar()
    : today_(getToday())
    , currentYear_(today_.getYear())
    , currentMonth_(today_.getMonth())
{
}

// Add an event to the calendar
void Calendar::addEvent(const Event& e) {
    events_.push_back(e);
}

// Remove an event; return true if removed, false if not found
bool Calendar::removeEvent(const Event& e) {
    for (auto it = events_.begin(); it != events_.end(); ++it) {
        if (*it == e) {
            events_.erase(it);
            return true;
        }
    }
    return false;
}

// Advance to the next month, rolling over year if needed
void Calendar::nextMonth() {
    if (currentMonth_ == 12) {
        currentMonth_ = 1;
        ++currentYear_;
    }
    else {
        ++currentMonth_;
    }
}

// Go back to the previous month, rolling back year if needed
void Calendar::prevMonth() {
    if (currentMonth_ == 1) {
        currentMonth_ = 12;
        --currentYear_;
    }
    else {
        --currentMonth_;
    }
}

// Manually set the displayed year and month
void Calendar::setMonth(int year, int month) {
    currentYear_ = year;
    currentMonth_ = month;
}

// Check if a given date corresponds to "today"
bool Calendar::isToday(int y, int m, int d) const {
    return today_.getYear() == y
        && today_.getMonth() == m
        && today_.getDay() == d;
}

// Check if any event is scheduled on the specified date
bool Calendar::hasEventOn(int y, int m, int d) const {
    for (auto& e : events_) {
        Date dd = e.getDate();
        if (dd.getYear() == y && dd.getMonth() == m && dd.getDay() == d) {
            return true;
        }
    }
    return false;
}

// Display the current month as a text calendar, marking today and events
void Calendar::displayMonth() const {
    // Header: Year / Month
    std::cout << "    " << currentYear_
        << " / " << std::setw(2) << std::setfill('0') << currentMonth_
        << std::setfill(' ') << "\nSu Mo Tu We Th Fr Sa\n";

    // Determine which weekday the 1st falls on (0=Sun..6=Sat)
    Date first(currentYear_, currentMonth_, 1);
    int startDow = first.dayOfWeek(); // 0=Sun..6=Sat
    int dim = daysInMonth(currentYear_, currentMonth_);

    // Print initial spacing before the first day
    for (int i = 0; i < startDow; ++i) {
        std::cout << "   ";
    }

    // Print each day of the month
    for (int day = 1; day <= dim; ++day) {
        bool today = isToday(currentYear_, currentMonth_, day);
        bool hasEvent = hasEventOn(currentYear_, currentMonth_, day);

        std::ostringstream cell;
        cell << std::setw(2) << day;
        if (hasEvent) cell << '*'; // Mark dates with events

        std::string s = cell.str();
        if (today) {
            // Enclose today in brackets
            s = "[" + s + "]";
        }
        else {
            // Ensure width of 3 if no brackets
            if (s.size() == 2) s = " " + s;
        }
        std::cout << s << ' ';

        // Line break at end of week
        if ((startDow + day) % 7 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

// Display all 12 months of the current year
void Calendar::displayYear() {
    int savedY = currentYear_, savedM = currentMonth_;
    for (int m = 1; m <= 12; ++m) {
        setMonth(currentYear_, m);
        displayMonth();
    }

    // Restore original month
    setMonth(savedY, savedM);
}

// Return events matching a specific type string
std::vector<Event> Calendar::getEventsByType(const std::string& type) const {
    std::vector<Event> res;
    for (auto& e : events_) {
        if (e.getType() == type) res.push_back(e);
    }
    return res;
}

// Return events with priority >= minPriority
std::vector<Event> Calendar::getEventsByPriority(int minPriority) const {
    std::vector<Event> res;
    for (auto& e : events_) {
        if (e.getPriority() >= minPriority) res.push_back(e);
    }
    return res;
}

// Return events whose date falls within the inclusive [from,to] range
std::vector<Event> Calendar::getEventsInRange(const Date& from, const Date& to) const {
    std::vector<Event> res;
    for (auto& e : events_) {
        Date d = e.getDate();
        if (d >= from && d <= to) res.push_back(e);
    }
    return res;
}

// Return events in the specified month and year
std::vector<Event> Calendar::getEventsInMonth(int year, int month) const {
    std::vector<Event> res;
    for (auto& e : events_) {
        Date d = e.getDate();
        if (d.getYear() == year && d.getMonth() == month) {
            res.push_back(e);
        }
    }
    return res;
}
