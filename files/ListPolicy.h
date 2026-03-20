#pragma once
#include <memory>
#include <stdexcept>


struct ListPolicy {

   
    template <typename T>
    struct Container {
    private:

        
        struct Node {
            T value;
            std::unique_ptr<Node> next;

            explicit Node(T val, std::unique_ptr<Node> nxt = nullptr)
                : value(std::move(val)), next(std::move(nxt)) {}
        };

        std::unique_ptr<Node> top_;
        std::size_t size_ = 0;

    public:


        void push(T value) {
            auto newNode = std::make_unique<Node>(std::move(value), std::move(top_));
            top_ = std::move(newNode);
            ++size_;
        }

        T pop() {
            if (isEmpty())
                throw std::underflow_error("pop() llamado en pila vacía.");
            T val = std::move(top_->value);
            top_ = std::move(top_->next); 
            --size_;
            return val;
        }

        const T& peek() const {
            if (isEmpty())
                throw std::underflow_error("peek() llamado en pila vacía.");
            return top_->value;
        }

        bool isEmpty() const { return top_ == nullptr; }

        std::size_t size() const { return size_; }
    };
};
