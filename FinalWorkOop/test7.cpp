#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "Screen.h"

// Tests for Task 7: Screen copy/move semantics and text editing
void testTask7() {
    const char* fn = "tmp_test7.txt";
    // Create file with one paragraph
    std::ofstream ofs(fn);
    ofs << "HelloWorld";
    ofs.close();

    // Original screen
    Screen original(fn, 1);
    // Copy constructor
    Screen copyScreen = original;
    // Move constructor
    Screen movedScreen = std::move(original);

    // Edit the copy: replace entire text
    copyScreen.editParagraph(0, "Hi");
    // Insert and delete
    copyScreen.insertText(0, 2, "XYZ");   // text = "HiXYZ"
    copyScreen.deleteText(0, 2, 3);         // back to "Hi"

    // Capture output of copyScreen
    std::ostringstream buf;
    auto* old = std::cout.rdbuf(buf.rdbuf());
    copyScreen.display();
    std::cout.rdbuf(old);
    std::string out = buf.str();
    assert(out.find("Hi") != std::string::npos);

    // Check movedScreen still shows original
    buf.str(""); buf.clear();
    old = std::cout.rdbuf(buf.rdbuf());
    movedScreen.display();
    std::cout.rdbuf(old);
    out = buf.str();
    assert(out.find("HelloWorld") != std::string::npos);

    // Cleanup
    std::remove(fn);
}

#ifdef TEST_MAIN
int main() {
    testTask6();
    testTask7();
    return 0;
}
#endif
