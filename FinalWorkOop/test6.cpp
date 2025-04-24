#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "Screen.h"

// Tests for Task 6: Screen loading and scrolling functionality
void testTask6() {
    const char* fn = "tmp_test6.txt";
    // Create file with 4 paragraphs
    std::ofstream ofs(fn);
    ofs << "ParaA Line1\nLine2" << std::endl << std::endl;
    ofs << "ParaB Line1\nLine2" << std::endl << std::endl;
    ofs << "ParaC Line1\nLine2" << std::endl << std::endl;
    ofs << "ParaD Line1\nLine2";
    ofs.close();

    // 2 paragraphs per page
    Screen screen(fn, 2);
    std::ostringstream buf;
    auto* old = std::cout.rdbuf(buf.rdbuf());

    // First page: ParaA, ParaB
    screen.display();
    std::cout.rdbuf(old);
    {
        std::string out = buf.str();
        assert(out.find("ParaA") != std::string::npos);
        assert(out.find("ParaB") != std::string::npos);
        assert(out.find("ParaC") == std::string::npos);
    }

    // Scroll forward: ParaC, ParaD
    buf.str(""); buf.clear();
    old = std::cout.rdbuf(buf.rdbuf());
    screen.scrollForward();
    screen.display();
    std::cout.rdbuf(old);
    {
        std::string out = buf.str();
        assert(out.find("ParaC") != std::string::npos);
        assert(out.find("ParaD") != std::string::npos);
    }

    // Scroll backward: back to ParaA, ParaB
    buf.str(""); buf.clear();
    old = std::cout.rdbuf(buf.rdbuf());
    screen.scrollBackward();
    screen.display();
    std::cout.rdbuf(old);
    assert(buf.str().find("ParaA") != std::string::npos);

    // Jump to paragraph 2 (0-based index) -> ParaC only
    buf.str(""); buf.clear();
    old = std::cout.rdbuf(buf.rdbuf());
    screen.setParagraphsPerPage(1);
    screen.jumpTo(2);
    screen.display();
    std::cout.rdbuf(old);
    assert(buf.str().find("ParaC") != std::string::npos);

    // Cleanup
    std::remove(fn);
}