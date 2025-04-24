#pragma once

#include <iostream>
#include <string>
#include "Date.h"
#include "Time.h"

class Event {
public:
    Event(const Date& date,
        const std::string& type,
        int priority,
        const std::string& title,
        const std::string& description);

    Event(const Date& date,
        const Time& time,
        const std::string& type,
        int priority,
        const std::string& title,
        const std::string& description);

    Date getDate() const;
    bool hasTime() const;
    Time getTime() const;
    std::string getType() const;
    int getPriority() const;
    std::string getTitle() const;
    std::string getDescription() const;

    void setDate(const Date& date);
    void setTime(const Time& time);
    void clearTime();  
    void setType(const std::string& type);
    void setPriority(int priority);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);

    friend std::ostream& operator<<(std::ostream& os, const Event& e);

    bool operator<(const Event& o) const;
    bool operator==(const Event& o) const;
    bool operator!=(const Event& o) const { return !(*this == o); }

private:
    Date date_;
    bool hasTime_;
    Time time_;
    std::string type_;
    int priority_;
    std::string title_;
    std::string description_;
};