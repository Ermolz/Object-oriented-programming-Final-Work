#include "Event.h"

#include <stdexcept>

// Constructor for an all-day event (no specific time)
Event::Event(const Date& date,
    const std::string& type,
    int priority,
    const std::string& title,
    const std::string& description)
    : date_(date)
    , hasTime_(false)
    , time_(0, 0, 0)
    , type_(type)
    , priority_(priority)
    , title_(title)
    , description_(description)
{
    // all-day event stores default time of 00:00:00 but marks hasTime_ = false
}

// Constructor for a timed event (includes specific time)
Event::Event(const Date& date,
    const Time& time,
    const std::string& type,
    int priority,
    const std::string& title,
    const std::string& description)
    : date_(date)
    , hasTime_(true)
    , time_(time)
    , type_(type)
    , priority_(priority)
    , title_(title)
    , description_(description)
{
    // timed event stores provided time and sets hasTime_ = true
}

// Get the event date
Date Event::getDate() const {
    return date_;
}

// Check if the event has a specific time
bool Event::hasTime() const {
    return hasTime_;
}

// Get the event time; throws if this is an all-day event
Time Event::getTime() const {
    if (!hasTime_) throw std::logic_error("Event has no time");
    return time_;
}

// Field getters
std::string Event::getType() const {
    return type_;
}


int Event::getPriority() const {
    return priority_;
}

std::string Event::getTitle() const {
    return title_;
}

std::string Event::getDescription() const {
    return description_;
}

// Field setters
void Event::setDate(const Date& date) {
    date_ = date;
}

void Event::setTime(const Time& time) {
    time_ = time;
    hasTime_ = true;
}

void Event::clearTime() {
    hasTime_ = false;
}

void Event::setType(const std::string& type) {
    type_ = type;
}

void Event::setPriority(int priority) {
    priority_ = priority;
}

void Event::setTitle(const std::string& title) {
    title_ = title;
}

void Event::setDescription(const std::string& description) {
    description_ = description;
}

// Stream insertion operator for formatted event output
// Format: yyyy-mm-dd [ hh:mm:ss ] | [Type] (prio=N) Title — Description
std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << e.date_;
    if (e.hasTime_) {
        os << ' ' << e.time_; // add time if present
    }
    os << " | [" << e.type_ << "]"
        << " (prio=" << e.priority_ << ") "
        << e.title_;
    if (!e.description_.empty()) {
        os << " — " << e.description_;
    }
    return os;
}

// Comparison operator: sorts first by date, then by time (all-day treated as 00:00)
bool Event::operator<(const Event& o) const {
    if (date_ < o.date_) return true;
    if (o.date_ < date_) return false;
    // If dates equal, compare times (all-day => Time(0,0,0))
    Time t1 = hasTime_ ? time_ : Time(0, 0, 0);
    Time t2 = o.hasTime_ ? o.time_ : Time(0, 0, 0);
    return t1 < t2;
}

// Equality operator: events are equal if date and time match
// (all-day events compared as 00:00)
bool Event::operator==(const Event& o) const {
    if (!(date_ == o.date_)) return false;
    Time t1 = hasTime_ ? time_ : Time(0, 0, 0);
    Time t2 = o.hasTime_ ? o.time_ : Time(0, 0, 0);
    return t1 == t2;
}
