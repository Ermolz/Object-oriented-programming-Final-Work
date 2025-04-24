#include "Screen.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Constructor: load paragraphs and set page size
Screen::Screen(const std::string& filename, int paragraphsPerPage)
    : paragraphsPerPage_(paragraphsPerPage), currentStart_(0)
{
    loadFromFile(filename); // Read file and split into paragraphs
}

// Load file content and split into paragraphs separated by empty lines
void Screen::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    std::ostringstream paragraph;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            // Empty line marks end of a paragraph
            if (!paragraph.str().empty()) {
                paragraphs_.push_back(paragraph.str());
                paragraph.str({}); // Clear the buffer
                paragraph.clear();
            }
        }
        else {
            // Append non-empty line to current paragraph
            paragraph << line << "\n";
        }
    }
    // Add last paragraph if any text remains
    if (!paragraph.str().empty()) {
        paragraphs_.push_back(paragraph.str());
    }
}

// Display the current page of paragraphs to stdout
void Screen::display() const {
    int end = std::min(static_cast<int>(paragraphs_.size()), currentStart_ + paragraphsPerPage_);
    for (int i = currentStart_; i < end; ++i) {
        std::cout << paragraphs_[i] << "\n";
    }
}

// Advance one page forward (do nothing if already at end)
void Screen::scrollForward() {
    if (currentStart_ + paragraphsPerPage_ < static_cast<int>(paragraphs_.size())) {
        currentStart_ += paragraphsPerPage_;
    }
}

// Move one page backward (cannot go before start)
void Screen::scrollBackward() {
    currentStart_ = std::max(0, currentStart_ - paragraphsPerPage_);
}

// Change number of paragraphs per page and reset to beginning
void Screen::setParagraphsPerPage(int paragraphsPerPage) {
    paragraphsPerPage_ = paragraphsPerPage;
    currentStart_ = 0;
}

// Jump directly to a specific paragraph index (0-based)
void Screen::jumpTo(int paragraphIndex) {
    if (paragraphIndex < 0 || paragraphIndex >= static_cast<int>(paragraphs_.size())) return;
    currentStart_ = paragraphIndex;
}

// Replace entire text of a single paragraph
void Screen::editParagraph(int paragraphIndex, const std::string& newText) {
    if (paragraphIndex < 0 || paragraphIndex >= static_cast<int>(paragraphs_.size())) return;
    paragraphs_[paragraphIndex] = newText;
}

// Insert text into a paragraph at given position (clamp to end)
void Screen::insertText(int paragraphIndex, size_t pos, const std::string& text) {
    if (paragraphIndex < 0 || paragraphIndex >= static_cast<int>(paragraphs_.size())) return;
    auto& para = paragraphs_[paragraphIndex];
    if (pos > para.size()) pos = para.size();
    para.insert(pos, text);
}

// Delete a substring from a paragraph starting at pos of length len
void Screen::deleteText(int paragraphIndex, size_t pos, size_t len) {
    if (paragraphIndex < 0 || paragraphIndex >= static_cast<int>(paragraphs_.size())) return;
    auto& para = paragraphs_[paragraphIndex];
    if (pos >= para.size()) return; // Nothing to delete
    para.erase(pos, len);
}