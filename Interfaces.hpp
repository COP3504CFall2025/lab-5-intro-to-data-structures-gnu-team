#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    std::size_t size;
public:
    void push(const T& item) = 0;
    T pop() = 0;
    T peek() const = 0;
    std::size_t getSize() const noexcept {return size;}
};


template <typename T>
class QueueInterface {
    std::size_t size;
public:
    void enqueue(const T& item);
    T dequeue();
    T peek() const;
    std::size_t getSize() const noexcept {return size;}
};


template <typename T>
class DequeInterface {
    std::size_t size;
public:
    void pushFront(const T& item);
    void pushBack(const T& item);
    T popFront();
    T popBack();
    const T& front() const;
    const  T& back() const;
    std::size_t getSize() const noexcept {return size;}
};

