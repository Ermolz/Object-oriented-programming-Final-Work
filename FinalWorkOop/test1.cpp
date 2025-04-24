#include <cassert>
#include <iostream>

#include "Date.h"
#include "Time.h"

// Tests for Task 1: Date and Time functionality
typedef void(*TEST_MAIN_TYPE)();

void testTask1() {
    // 1.1. Constructors and getters
    Date d(2025, 4, 24);
    assert(d.getYear() == 2025);
    assert(d.getMonth() == 4);
    assert(d.getDay() == 24);

    // 1.2. Day of week for 2025-04-24 — Thursday (0=Sunday,1=Monday,...4=Thursday)
    assert(d.dayOfWeek() == 4);

    // 1.3. Increment and decrement operators
    Date d1 = d;
    ++d1;
    assert(d1 == Date(2025, 4, 25));
    d1 = d;
    d1++;
    assert(d1 == Date(2025, 4, 25));
    d1 = d;
    --d1;
    assert(d1 == Date(2025, 4, 23));
    d1 = d;
    d1--;
    assert(d1 == Date(2025, 4, 23));

    // 1.4. +n/-n arithmetic and assignment operators
    assert((d + 7) == Date(2025, 5, 1));
    assert((d - 24) == Date(2025, 3, 31));
    Date d2 = d;
    d2 += 30;
    assert(d2 == Date(2025, 5, 24));
    d2 -= 30;
    assert(d2 == d);

    // 1.5. Comparison operators
    assert(Date(2025, 1, 1) < Date(2025, 1, 2));
    assert(Date(2025, 1, 1) <= Date(2025, 1, 1));
    assert(Date(2025, 1, 2) > Date(2025, 1, 1));
    assert(Date(2025, 1, 2) >= Date(2025, 1, 2));
    assert(Date(2025, 1, 1) != Date(2025, 1, 2));

    // 1.6. Invalid dates should throw exceptions
    try {
        Date bad1(2025, 13, 1);
        assert(false);
    }
    catch (const std::invalid_argument&) {}
    try {
        Date bad2(2025, 2, 29); // 2025 is not a leap year
        assert(false);
    }
    catch (const std::invalid_argument&) {}

    // 1.7. Time constructors and getters
    Time t(23, 59, 58);
    assert(t.getHour() == 23);
    assert(t.getMinute() == 59);
    assert(t.getSecond() == 58);

    // 1.8. ++/-- by one second
    Time t1 = t;
    ++t1;
    assert(t1 == Time(23, 59, 59));
    t1 = t;
    t1++;
    assert(t1 == Time(23, 59, 59));
    Time t2(0, 0, 0);
    --t2;
    assert(t2 == Time(23, 59, 59));

    // 1.9. Arithmetic operations on Time (in seconds)
    Time t3 = Time(1, 0, 0) + 3661;  // +1 hour, 1 minute, 1 second
    assert(t3 == Time(2, 1, 1));
    Time t4 = Time(0, 0, 30) - 60;   // -1 minute
    assert(t4 == Time(23, 59, 30));

    // 1.10. Time comparison operators
    assert(Time(0, 0, 1) < Time(0, 0, 2));
    assert(Time(5, 0, 0) >= Time(5, 0, 0));
    assert(Time(23, 59, 59) > Time(0, 0, 0));

    // 1.11. Invalid time values should throw exceptions
    try {
        Time badt(24, 0, 0);
        assert(false);
    }
    catch (const std::invalid_argument&) {}
}

#ifdef TEST_MAIN
int main() {
    testTask1();
    return 0;
}
#endif