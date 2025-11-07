#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    //Printing
    void PrintForward() const;
    void PrintReverse() const;
};

template <typename T>
void LLQ<T>::enqueue(const T& item) {
    list.addTail(item);
}

template <typename T>
T LLQ<T>::dequeue() {
    if(list.getHead() == nullptr) {
        throw std::runtime_error("ERROR: dequeue() on empty queue.");
    }
    T result = list.getTail()->datum;
    list.removeTail();
    return result;
}

template <typename T>
T LLQ<T>::peek() const {
    LinkedList::Node* result = list.getHead()
    if(result == nullptr) {
        throw std::runtime_error("ERROR: peek() on empty queue.");
    }
    return result->datum;
}

template <typename T>
void LLQ<T>::PrintForward() const {
    list.printForward();
}

template <typename T>
void LLQ<T>::PrintReverse() const {
    list.printReverse();
}