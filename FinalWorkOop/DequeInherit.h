#pragma once

#include "ArrayDeque.h"
#include "ListDeque.h"

template<typename T, template<typename> class Impl>
class DequeInherit : public Impl<T> {
    // Nothing extra: uses base Impl methods
};