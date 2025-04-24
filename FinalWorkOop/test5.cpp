#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "Calendar.h"
#include "Date.h"
#include "Event.h"

// Tests for Task 5: Birthday weekdays via Calendar and display markers
void testTask5() {
    // Known weekdays for test dates
    const char* WEEKDAYS[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
    std::vector<std::pair<std::string, Date>> birthdays = {
        {"TestUser", Date(2000, 1, 1)},  // Saturday
        {"Einstein", Date(1879, 3, 14)}   // Friday
    };

    Calendar cal;
    std::ostringstream out;
    auto* oldBuf = std::cout.rdbuf(out.rdbuf());

    for (auto& bd : birthdays) {
        const auto& name = bd.first;
        const auto& d = bd.second;
        // Add as event for calendar marking
        cal.addEvent(Event(d, "Birthday", 1, name, ""));
        // Print weekday info
        std::cout << name << " was born on " << d
            << ", which was a " << WEEKDAYS[d.dayOfWeek()] << "\n";
        // Display calendar for that month
        cal.setMonth(d.getYear(), d.getMonth());
        cal.displayMonth();
    }

    std::cout.rdbuf(oldBuf);
    std::string s = out.str();

    // Assert weekday lines present
    assert(s.find("TestUser was born on 2000-01-01, which was a Saturday") != std::string::npos);
    assert(s.find("Einstein was born on 1879-03-14, which was a Friday") != std::string::npos);
    // Assert calendar markers '*' appear on the correct dates (note space-padded day)
    assert(s.find(" 1*") != std::string::npos);
    assert(s.find("14*") != std::string::npos);
}

#ifdef TEST_MAIN
int main() {
    testTask5();
    return 0;
}
#endif
