#pragma once

#include "Deque.h"
#include "ArrayDeque.h"
#include "ListDeque.h"

// Composition implementation: wraps an Impl<T> internally
template<typename T, template<typename> class Impl>
class DequeCompose : public Deque<T> {
protected:
    void doPushFront(const T& v) override { impl_.pushFront(v); }
    void doPushBack(const T& v) override { impl_.pushBack(v); }
    void doPopFront() override { impl_.popFront(); }
    void doPopBack()  override { impl_.popBack(); }

    T& doFront() override { return impl_.front(); }
    const T& doFront() const override { return impl_.front(); }
    T& doBack() override { return impl_.back(); }
    const T& doBack() const override { return impl_.back(); }

    bool doEmpty() const override { return impl_.empty(); }
    std::size_t doSize() const override { return impl_.size(); }

private:
    Impl<T> impl_;
};