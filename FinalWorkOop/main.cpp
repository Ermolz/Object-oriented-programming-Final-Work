#include <iostream>

// Declarations of test functions
void testTask1();
void testTask2();
void testTask3();
void testTask4();
void testTask5();
void testTask6();
void testTask7();
void testTask8();
void testTask9();
void testTask10();

int main() {
    std::cout << "Running all tests..." << std::endl;

    testTask1();
    std::cout << "[OK] Task 1 (Date & Time) tests passed\n";

    testTask2();
    std::cout << "[OK] Task 2 (Event) tests passed\n";

    testTask3();
    std::cout << "[OK] Task 3 (Calendar) tests passed" << std::endl;

    testTask4();
    std::cout << "[OK] Task 4 (Semester end) tests passed" << std::endl;

    testTask5();
    std::cout << "[OK] Task 5 (Birthdays) tests passed" << std::endl;

    testTask6();
    std::cout << "[OK] Task 6 (Screen) tests passed" << std::endl;

    testTask7();
    std::cout << "[OK] Task 7 (Screen copy/move & edit) tests passed" << std::endl;

    testTask8();
    std::cout << "[OK] Task 8 (Dictionary) tests passed" << std::endl;

    testTask9();
    std::cout << "[OK] Task 9 (Deque NVI) tests passed" << std::endl;

    testTask10();
    std::cout << "[OK] Task 10 (Inheritance vs Composition) tests passed" << std::endl;


    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}