#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Screen {
public:
    Screen(const std::string& filename, int paragraphsPerPage);

    Screen(const Screen& other) = default;
    Screen(Screen&& other) noexcept = default;
    Screen& operator=(const Screen& other) = default;
    Screen& operator=(Screen&& other) noexcept = default;

    void display() const;

    void scrollForward();
    void scrollBackward();

    void setParagraphsPerPage(int paragraphsPerPage);

    void jumpTo(int paragraphIndex);

    void editParagraph(int paragraphIndex, const std::string& newText);

    void insertText(int paragraphIndex, size_t pos, const std::string& text);

    void deleteText(int paragraphIndex, size_t pos, size_t len);

private:
    std::vector<std::string> paragraphs_;
    int paragraphsPerPage_;
    int currentStart_;

    void loadFromFile(const std::string& filename);
};
