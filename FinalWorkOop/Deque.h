#pragma once

#include <cstddef>

template<typename T>
class Deque {
public:
    Deque() = default;
    virtual ~Deque() = default;

    // Public interface methods (not virtual)
    void pushFront(const T& v) { doPushFront(v); }
    void pushBack(const T& v) { doPushBack(v); }
    void popFront() { doPopFront(); }
    void popBack() { doPopBack(); }

    T& front() { return doFront(); }
    const T& front()     const { return doFront(); }
    T& back() { return doBack(); }
    const T& back()      const { return doBack(); }

    bool     empty()      const { return doEmpty(); }
    std::size_t size()    const { return doSize(); }

protected:
    virtual void doPushFront(const T&) = 0;
    virtual void doPushBack(const T&) = 0;
    virtual void doPopFront() = 0;
    virtual void doPopBack() = 0;

    virtual T& doFront() = 0;
    virtual const T& doFront() const = 0;
    virtual T& doBack() = 0;
    virtual const T& doBack() const = 0;

    virtual bool doEmpty() const = 0;
    virtual std::size_t doSize() const = 0;
};
