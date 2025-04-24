#include "Dictionary.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

//  Internal helper: add or update a single word entry 
void Dictionary::addWord(const std::string& w) {
    auto it = indexMap_.find(w);
    if (it == indexMap_.end()) {
        entries_.push_back({ w, 1, Status::New });
        indexMap_[w] = static_cast<int>(entries_.size()) - 1;
    }
    else {
        entries_[it->second].freq++;
    }
}

//  Constructor: build dictionary directly from a file 
Dictionary::Dictionary(const std::string& filename) {
    buildFromFile(filename);
}

//  Read entire file, parse words, and populate the dictionary 
void Dictionary::buildFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    // Read file into a single string
    std::string text((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::string word;
    for (char c : text) {
        if (std::isalpha((unsigned char)c)) {
            // Build word in lowercase
            word += static_cast<char>(std::tolower((unsigned char)c));
        }
        else {
            // Non-letter encountered: finalize current word
            if (!word.empty()) {
                addWord(word);
                word.clear();
            }
        }
    }

    // Add last word if file didn't end on non-letter
    if (!word.empty()) addWord(word);
}

//  Set the learning status for a given word (if it exists) 
void Dictionary::setStatus(const std::string& word, Status status) {
    auto it = indexMap_.find(word);
    if (it != indexMap_.end()) {
        entries_[it->second].status = status;
    }
}

//  Retrieve the status of a word, or throw if not found 
Dictionary::Status Dictionary::getStatus(const std::string& word) const {
    auto it = indexMap_.find(word);
    if (it != indexMap_.end()) {
        return entries_[it->second].status;
    }
    throw std::out_of_range("Word not found: " + word);
}

//  Sort entries alphabetically by word 
void Dictionary::sortByLex() {
    std::sort(entries_.begin(), entries_.end(), [](auto& a, auto& b) {
        return a.word < b.word;
        });

    // Rebuild indexMap_ after sorting
    indexMap_.clear();
    for (int i = 0; i < (int)entries_.size(); ++i) {
        indexMap_[entries_[i].word] = i;
    }
}

//  Sort entries by descending frequency, then alphabetically 
void Dictionary::sortByFrequency() {
    std::sort(entries_.begin(), entries_.end(), [](auto& a, auto& b) {
        if (a.freq != b.freq) return a.freq > b.freq;
        return a.word < b.word;
        });

    // Rebuild indexMap_ after sorting
    indexMap_.clear();
    for (int i = 0; i < (int)entries_.size(); ++i) {
        indexMap_[entries_[i].word] = i;
    }
}

//  Return a new dictionary merging this and another: sums frequencies,
//  and takes the "more advanced" status between conflicts 
Dictionary Dictionary::unionWith(const Dictionary& other) const {
    Dictionary result = *this;
    for (auto& e : other.entries_) {
        auto it = result.indexMap_.find(e.word);
        if (it == result.indexMap_.end()) {
            // Word not present: copy entry
            result.entries_.push_back(e);
            result.indexMap_[e.word] = static_cast<int>(result.entries_.size()) - 1;
        }
        else {
            // Word present: update frequency and status
            auto& dst = result.entries_[it->second];
            dst.freq = dst.freq + e.freq;

            // Keep the higher status (enum comparison)
            dst.status = (dst.status < e.status ? e.status : dst.status);
        }
    }
    return result;
}

//  Return a new dictionary intersecting this and another: keeps words in both,
//  with frequency = min, and status = min (least advanced) 
Dictionary Dictionary::intersectWith(const Dictionary& other) const {
    Dictionary result;
    for (auto& e : entries_) {
        auto it = other.indexMap_.find(e.word);
        if (it != other.indexMap_.end()) {
            int f2 = other.entries_[it->second].freq;
            // Pick the lesser status (e.g. New < Learning)
            Dictionary::Status s2 = other.entries_[it->second].status;
            result.entries_.push_back({ e.word, std::min(e.freq, f2),
                                      (e.status < s2 ? e.status : s2) });
        }
    }

    // Rebuild indexMap_
    for (int i = 0; i < (int)result.entries_.size(); ++i) {
        result.indexMap_[result.entries_[i].word] = i;
    }
    return result;
}

//  Convert Status enum to human-readable string 
std::string Dictionary::statusToString(Status s) {
    switch (s) {
    case Status::New:       return "New";
    case Status::Learning:  return "Learning";
    case Status::Learned:   return "Learned";
    case Status::Ignored:   return "Ignored";
    }
    return "";
}

//  Print the dictionary to stdout in tabular form: Word, Freq, Status 
void Dictionary::print() const {
    std::cout << "Word\tFreq\tStatus\n";
    for (auto& e : entries_) {
        std::cout << e.word << "\t" << e.freq << "\t"
            << statusToString(e.status) << "\n";
    }
}
