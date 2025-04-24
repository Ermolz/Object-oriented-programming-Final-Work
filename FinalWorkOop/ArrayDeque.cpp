#include "ArrayDeque.h"

// Constructor
template<typename T>
ArrayDeque<T>::ArrayDeque(std::size_t cap)
    : buf_(cap), head_(0), tail_(0), cnt_(0) {
}

// Push to front
template<typename T>
void ArrayDeque<T>::doPushFront(const T& v) {
    ensureCapacity();
    head_ = (head_ + buf_.size() - 1) % buf_.size();
    buf_[head_] = v;
    ++cnt_;
}

// Push to back
template<typename T>
void ArrayDeque<T>::doPushBack(const T& v) {
    ensureCapacity();
    buf_[tail_] = v;
    tail_ = (tail_ + 1) % buf_.size();
    ++cnt_;
}

// Pop from front
template<typename T>
void ArrayDeque<T>::doPopFront() {
    if (cnt_ == 0) throw std::out_of_range("popFront on empty");
    head_ = (head_ + 1) % buf_.size();
    --cnt_;
}

// Pop from back
template<typename T>
void ArrayDeque<T>::doPopBack() {
    if (cnt_ == 0) throw std::out_of_range("popBack on empty");
    tail_ = (tail_ + buf_.size() - 1) % buf_.size();
    --cnt_;
}

// Access front element
template<typename T>
T& ArrayDeque<T>::doFront() {
    if (cnt_ == 0) throw std::out_of_range("front on empty");
    return buf_[head_];
}

// Access front element (const)
template<typename T>
const T& ArrayDeque<T>::doFront() const {
    if (cnt_ == 0) throw std::out_of_range("front on empty");
    return buf_[head_];
}

// Access back element
template<typename T>
T& ArrayDeque<T>::doBack() {
    if (cnt_ == 0) throw std::out_of_range("back on empty");
    return buf_[(tail_ + buf_.size() - 1) % buf_.size()];
}

// Access back element (const)
template<typename T>
const T& ArrayDeque<T>::doBack() const {
    if (cnt_ == 0) throw std::out_of_range("back on empty");
    return buf_[(tail_ + buf_.size() - 1) % buf_.size()];
}

// Check empty
template<typename T>
bool ArrayDeque<T>::doEmpty() const {
    return cnt_ == 0;
}

// Get size
template<typename T>
std::size_t ArrayDeque<T>::doSize() const {
    return cnt_;
}

template<typename T>
void ArrayDeque<T>::ensureCapacity() {
    if (cnt_ < buf_.size()) return;
    std::size_t old = buf_.size();
    std::vector<T> newBuf(old * 2);
    for (std::size_t i = 0; i < cnt_; ++i) {
        newBuf[i] = buf_[(head_ + i) % old];
    }
    buf_.swap(newBuf);
    head_ = 0;
    tail_ = cnt_;
}


template class ArrayDeque<int>;