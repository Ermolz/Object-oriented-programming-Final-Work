#include <cassert>
#include <iostream>

#include "Date.h"

// Tests for Task 4: Semester end date calculation
void testTask4() {
    // Case 1: starting at beginning of year (16 weeks = 112 days)
    {
        Date start(2025, 1, 1);
        Date end = start + 16 * 7;
        assert(end == Date(2025, 4, 23));
    }
    // Case 2: crossing month boundary (4 weeks = 28 days)
    {
        Date start(2025, 2, 15);
        Date end = start + 4 * 7;
        assert(end == Date(2025, 3, 15));
    }
    // Case 3: crossing year boundary
    {
        Date start(2023, 11, 1);
        Date end = start + 10 * 7;  // 70 days
        assert(end == Date(2024, 1, 10));  // corrected expectation
    }
    // Case 4: leap day start
    {
        Date start(2024, 2, 29);
        Date end = start + 1 * 7;
        assert(end == Date(2024, 3, 7));
    }
    // Case 5: zero weeks
    {
        Date start(2025, 7, 20);
        Date end = start + 0;
        assert(end == start);
    }
}

#ifdef TEST_MAIN
int main() {
    testTask4();
    return 0;
}
#endif