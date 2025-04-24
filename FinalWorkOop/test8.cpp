#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>

#include "Dictionary.h"

// Tests for Task 8: Dictionary functionality
void testTask8() {
    const char* file1 = "tmp_dict1.txt";
    std::ofstream(file1) << "apple apple Banana cherry banana";

    Dictionary dict;
    dict.buildFromFile(file1);
    // Frequencies: apple=2, banana=2, cherry=1
    assert(dict.getStatus("apple") == Dictionary::Status::New);
    assert(dict.getStatus("banana") == Dictionary::Status::New);
    assert(dict.getStatus("cherry") == Dictionary::Status::New);

    // Set and get status
    dict.setStatus("banana", Dictionary::Status::Learning);
    assert(dict.getStatus("banana") == Dictionary::Status::Learning);

    // Lex sort
    dict.sortByLex();
    std::ostringstream buf1;
    auto* old1 = std::cout.rdbuf(buf1.rdbuf());
    dict.print();
    std::cout.rdbuf(old1);
    std::string out1 = buf1.str();
    assert(out1.find("apple") < out1.find("banana"));
    assert(out1.find("banana") < out1.find("cherry"));

    // Frequency sort
    dict.sortByFrequency();
    std::ostringstream buf2;
    auto* old2 = std::cout.rdbuf(buf2.rdbuf());
    dict.print();
    std::cout.rdbuf(old2);
    std::string out2 = buf2.str();
    // apple & banana both freq=2, then cherry
    assert(out2.find("apple") < out2.find("cherry"));

    // Union and intersect
    const char* file2 = "tmp_dict2.txt";
    std::ofstream(file2) << "banana Durian";
    Dictionary d2;
    d2.buildFromFile(file2);
    d2.setStatus("durian", Dictionary::Status::Ignored);

    auto u = dict.unionWith(d2);
    assert(u.getStatus("banana") == Dictionary::Status::Learning);
    assert(u.getStatus("durian") == Dictionary::Status::Ignored);

    auto inter = dict.intersectWith(d2);
    assert(inter.getStatus("banana") == Dictionary::Status::New);
    bool hasDurian = true;
    try { inter.getStatus("durian"); }
    catch (...) { hasDurian = false; }
    assert(!hasDurian);

    // Cleanup
    std::remove(file1);
    std::remove(file2);
    
}

#ifdef TEST_MAIN
int main() {
    testTask8();
    return 0;
}
#endif