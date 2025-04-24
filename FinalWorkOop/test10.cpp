#include <cassert>
#include <iostream>

#include "DequeInherit.h"
#include "DequeCompose.h"
#include "ArrayDeque.h"
#include "ListDeque.h"

// Tests for Task 10: comparing inheritance vs composition implementations
void testTask10() {
    // Closed inheritance
    DequeInherit<int, ArrayDeque> di;
    di.pushBack(1); di.pushFront(2);
    assert(di.front() == 2 && di.back() == 1);

    // Composition
    DequeCompose<int, ListDeque> dc;
    dc.pushBack(5); dc.pushFront(6);
    assert(dc.front() == 6 && dc.back() == 5);

    // Both should throw on underflow
    di.popFront(); di.popBack();
    dc.popFront(); dc.popBack();
    bool t1 = false, t2 = false;
    try { di.back(); }
    catch (...) { t1 = true; }
    try { dc.front(); }
    catch (...) { t2 = true; }
    assert(t1 && t2);
}

#ifdef TEST_MAIN
int main() {
    testTask10();
    return 0;
}
#endif
