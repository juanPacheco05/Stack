#pragma once
#include "ListPolicy.h"

template <typename T, typename Policy = ListPolicy>
class MyStack {
private:
    typename Policy::template Container<T> storage_;

public:

    void push(T value) {
        storage_.push(std::move(value));
    }


    T pop() {
        return storage_.pop();
    }


    const T& peek() const {
        return storage_.peek();
    }

    bool isEmpty() const {
        return storage_.isEmpty();
    }

    std::size_t size() const {
        return storage_.size();
    }
};
