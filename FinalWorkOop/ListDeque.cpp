#include "ListDeque.h"

template<typename T>
void ListDeque<T>::doPushFront(const T& v) {
    data_.push_front(v);
}

template<typename T>
void ListDeque<T>::doPushBack(const T& v) {
    data_.push_back(v);
}

template<typename T>
void ListDeque<T>::doPopFront() {
    if (data_.empty()) throw std::out_of_range("popFront on empty");
    data_.pop_front();
}

template<typename T>
void ListDeque<T>::doPopBack() {
    if (data_.empty()) throw std::out_of_range("popBack on empty");
    data_.pop_back();
}

template<typename T>
T& ListDeque<T>::doFront() {
    if (data_.empty()) throw std::out_of_range("front on empty");
    return data_.front();
}

template<typename T>
const T& ListDeque<T>::doFront() const {
    if (data_.empty()) throw std::out_of_range("front on empty");
    return data_.front();
}

template<typename T>
T& ListDeque<T>::doBack() {
    if (data_.empty()) throw std::out_of_range("back on empty");
    return data_.back();
}

template<typename T>
const T& ListDeque<T>::doBack() const {
    if (data_.empty()) throw std::out_of_range("back on empty");
    return data_.back();
}

template<typename T>
bool ListDeque<T>::doEmpty() const {
    return data_.empty();
}

template<typename T>
std::size_t ListDeque<T>::doSize() const {
    return data_.size();
}

template class ListDeque<int>;