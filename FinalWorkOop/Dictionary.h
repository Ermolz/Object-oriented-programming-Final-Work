#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Dictionary {
public:
    enum class Status { New, Learning, Learned, Ignored };

    Dictionary() = default;
    explicit Dictionary(const std::string& filename);

    void buildFromFile(const std::string& filename);

    void setStatus(const std::string& word, Status status);
    Status getStatus(const std::string& word) const;

    void sortByLex();
    void sortByFrequency();

    Dictionary unionWith(const Dictionary& other) const;
    Dictionary intersectWith(const Dictionary& other) const;

    void print() const;

private:
    struct Entry {
        std::string word;
        int freq;
        Status status;
    };

    std::vector<Entry> entries_;
    std::unordered_map<std::string, int> indexMap_;

    void addWord(const std::string& word);

    static std::string statusToString(Status s);
};