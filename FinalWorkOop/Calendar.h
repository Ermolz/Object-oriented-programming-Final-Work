#pragma once

#include <vector>
#include <string>
#include "Date.h"
#include "Event.h"

class Calendar {
public:
    Calendar();

    void addEvent(const Event& e);
    bool removeEvent(const Event& e);

    void nextMonth();
    void prevMonth();
    void setMonth(int year, int month);

    void displayMonth() const;
    void displayYear();

    std::vector<Event> getEventsByType(const std::string& type) const;
    std::vector<Event> getEventsByPriority(int minPriority) const;
    std::vector<Event> getEventsInRange(const Date& from, const Date& to) const;
    std::vector<Event> getEventsInMonth(int year, int month) const;

private:
    int currentYear_;
    int currentMonth_;
    Date today_;
    std::vector<Event> events_;

    static Date getToday();

    bool isToday(int year, int month, int day) const;
    bool hasEventOn(int year, int month, int day) const;
};
