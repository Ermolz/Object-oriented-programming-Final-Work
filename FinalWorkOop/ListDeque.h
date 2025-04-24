#pragma once

#include "Deque.h"
#include <list>
#include <stdexcept>

template<typename T>
class ListDeque : public Deque<T> {
protected:
    void doPushFront(const T& v) override;
    void doPushBack(const T& v) override;

    void doPopFront() override;
    void doPopBack() override;

    T& doFront() override;
    const T& doFront() const override;

    T& doBack() override;
    const T& doBack() const override;

    bool doEmpty() const override;
    std::size_t doSize() const override;

private:
    std::list<T> data_;
};