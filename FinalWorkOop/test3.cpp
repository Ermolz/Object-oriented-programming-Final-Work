#include <cassert>
#include <iostream>

#include "Calendar.h"
#include "Event.h"
#include "Date.h"
#include "Time.h"

// Tests for Task 3: Calendar functionality
void testTask3() {
    Calendar cal;
    // Test adding events
    Event eA(Date(2025, 5, 1), Time(8, 0, 0), "TypeA", 1, "EventA", "");
    Event eB(Date(2025, 5, 2), "TypeB", 2, "EventB", "");
    assert(cal.removeEvent(eA) == false);  // nothing to remove
    cal.addEvent(eA);
    cal.addEvent(eB);
    // Test getEventsByType
    auto vA = cal.getEventsByType("TypeA");
    assert(vA.size() == 1 && vA[0].getTitle() == "EventA");
    auto vX = cal.getEventsByType("Unknown");
    assert(vX.empty());
    // Test getEventsByPriority
    auto high = cal.getEventsByPriority(2);
    assert(high.size() == 1 && high[0].getType() == "TypeB");
    // Test getEventsInMonth
    auto mayEvents = cal.getEventsInMonth(2025, 5);
    assert(mayEvents.size() == 2);
    // Test removeEvent
    assert(cal.removeEvent(eA) == true);
    auto afterRemove = cal.getEventsByType("TypeA");
    assert(afterRemove.empty());
    // Test date range filtering
    Date from(2025, 5, 2), to(2025, 5, 3);
    auto range = cal.getEventsInRange(from, to);
    assert(range.size() == 1 && range[0].getDate() == Date(2025, 5, 2));
    // Test navigation: nextMonth and prevMonth via month-based filtering
    cal.setMonth(2025, 5);
    auto eventsMay = cal.getEventsInMonth(2025, 5);
    cal.nextMonth();
    auto eventsJun = cal.getEventsInMonth(2025, 6);
    assert(eventsJun.empty());
    cal.prevMonth();
    assert(cal.getEventsInMonth(2025, 5).size() == eventsMay.size());
}

#ifdef TEST_MAIN
int main() {
    testTask3();
    return 0;
}
#endif