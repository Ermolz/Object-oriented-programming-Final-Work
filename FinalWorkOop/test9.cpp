#include <cassert>
#include <iostream>

#include "Deque.h"
#include "ArrayDeque.h"
#include "ListDeque.h"

// Tests for Task 9: NVI interface implementations using ArrayDeque and ListDeque
void testTask9() {
    // test both implementations through the interface type
    for (int impl = 0; impl < 2; ++impl) {
        if (impl == 0) {
            ArrayDeque<int> a;
            Deque<int>& dq = a;
            assert(dq.empty());
            dq.pushBack(1);
            dq.pushFront(2);
            assert(dq.size() == 2);
            assert(dq.front() == 2 && dq.back() == 1);
            dq.popFront(); dq.popBack();
            bool thrown = false;
            try { dq.popFront(); }
            catch (...) { thrown = true; }
            assert(thrown);
        }
        else {
            ListDeque<int> l;
            Deque<int>& dq = l;
            assert(dq.empty());
            dq.pushBack(3);
            dq.pushFront(4);
            assert(dq.front() == 4 && dq.back() == 3);
            dq.popFront(); dq.popBack();
            bool thrown = false;
            try { dq.popBack(); }
            catch (...) { thrown = true; }
            assert(thrown);
        }
    }
}

#ifdef TEST_MAIN
int main() {
    testTask9();
    return 0;
}
#endif