#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Event.h"
#include "Date.h"
#include "Time.h"

// Tests for Task 2: Event functionality
void testTask2() {
    // 2.1. All-day event constructor
    Event e1(Date(2025, 5, 1), "Holiday", 1, "Spring Day", "");
    assert(!e1.hasTime());
    try {
        e1.getTime();
        assert(false);
    }
    catch (const std::logic_error&) {}

    // 2.2. Timed event constructor
    Event e2(Date(2025, 5, 1), Time(9, 0, 0), "Meeting", 5, "Team Sync", "Discuss Q2 targets");
    assert(e2.hasTime());
    assert(e2.getTime() == Time(9, 0, 0));

    // 2.3. Field getters
    assert(e2.getDate() == Date(2025, 5, 1));
    assert(e2.getType() == "Meeting");
    assert(e2.getPriority() == 5);
    assert(e2.getTitle() == "Team Sync");
    assert(e2.getDescription() == "Discuss Q2 targets");

    // 2.4. Field setters
    e2.setType("Call");
    e2.setPriority(2);
    e2.setTitle("Client Call");
    e2.setDescription("Call with client");
    assert(e2.getType() == "Call");
    assert(e2.getPriority() == 2);
    assert(e2.getTitle() == "Client Call");
    assert(e2.getDescription() == "Call with client");

    // 2.5. clearTime should remove time from event
    e2.clearTime();
    assert(!e2.hasTime());

    // 2.6. Comparison by date and time
    std::vector<Event> evs = {
        Event(Date(2025,5,1), Time(10,0,0), "A",1,"A",""),
        Event(Date(2025,5,1),             "B",2,"B",""),
        Event(Date(2025,4,30), Time(18,0,0),"C",3,"C","")
    };
    std::sort(evs.begin(), evs.end());
    // expected order: 2025-04-30 18:00, all-day 2025-05-01, 10:00 2025-05-01
    assert(evs[0].getDate() == Date(2025, 4, 30));
    assert(!evs[1].hasTime());
    assert(evs[2].hasTime());
    assert(evs[2].getTime() == Time(10, 0, 0));

    // 2.7. Formatted output contains date, time, type, priority, and title
    std::ostringstream os;
    os << evs[2];
    std::string s = os.str();
    assert(s.find("2025-05-01") != std::string::npos);
    assert(s.find("10:00:00") != std::string::npos);
    assert(s.find("[C]") == std::string::npos); // type is inside []
    assert(s.find("[B]") != std::string::npos || s.find("[A]") != std::string::npos);
}

#ifdef TEST_MAIN
int main() {
    testTask2();
    return 0;
}
#endif