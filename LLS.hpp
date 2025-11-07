#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;\

    //Printing
    void PrintForward() const;
    void PrintReverse() const;
};

template <typename T>
void LLS<T>::push(const T& item) {
    list.addTail(item);
}

template <typename T>
T LLS<T>::pop() {
    if(list->getHead() == nullptr) {
        throw std::runtime_error("ERROR: pop() on empty stack");
    }
    T result = list.getHead()->datum;
    list.removeHead();
    return result->datum;
}

template <typename T>
T LLS<T>::peek() const {
    if(list.getCount == 0) {
        throw std::runtime_error("ERROR: peek() on empty stack");
    }
    return list.getHead();
}

template <typename T>
size_t LLS<T>::getSize() const noexcept {return list.getCount();}

template <typename T>
void LLS<T>::PrintForward() const {
    list.printForward();
}

template <typename T>
void LLS<T>::PrintReverse() const {
    list.printReverse();
}