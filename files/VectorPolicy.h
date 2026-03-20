#pragma once
#include <vector>
#include <stdexcept>



struct VectorPolicy {

    template <typename T>
    struct Container {
    private:

        std::vector<T> data_;

    public:

        void push(T value) {
            data_.push_back(std::move(value));
        }

        T pop() {
            if (isEmpty())
                throw std::underflow_error("pop() llamado en pila vacía.");
            T val = std::move(data_.back());
            data_.pop_back();
            return val;
        }

        const T& peek() const {
            if (isEmpty())
                throw std::underflow_error("peek() llamado en pila vacía.");
            return data_.back();
        }

        bool isEmpty() const { return data_.empty(); }

        /** @return Número de elementos. */
        std::size_t size() const { return data_.size(); }
    };
};
