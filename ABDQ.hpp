#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

// Used https://www.youtube.com/watch?v=8sjFA-IX-Ww to understand how a Circular Queue works

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    //Helper
    void resize();

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ();

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    // Helper
    void print() const;

};

// Default Constructor
template <typename T>
ABDQ<T>::ABDQ()
    : data_(new T[4]),
      capacity_(4),
      size_(0),
      front_(0),
      back_(0) {}

// Parameterized Constructor
template <typename T>
ABDQ<T>::ABDQ(size_t capacity)
    : data_(new T[capacity]),
      capacity_(capacity),
      size_(0),
      front_(0),
      back_(0) {}

// Copy Constructor
template <typename T>
ABDQ<T>::ABDQ(const ABDQ& other) {
    this->data_ = new T[other.capacity_];
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    this->front_ = 0;
    this->back_ = size_;

    for(int i = front_; i < size_; ++i) {
        size_t index = (front_ + i) % capacity_;
        this->data_[i] = other.data_[index];
    }
}

// Copy Assignment
template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ& rhs) {
    if(this == &rhs) {
        return *this;
    }

    T* temp_array = new T[rhs.capacity_];
    delete[] this->array_;
    this->array_ = temp_array;
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    this->front_ = 0;
    this->back_ = size_;

    for(int i = front_; i < size_; ++i) {
        size_t index = (front_ + i) % capacity_;
        this->data_[i] = rhs.data_[index];
    }

    return *this;
}

// Move Constructor
template <typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept {
    this->data_ = other.data_;
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    this->front_ = other.front_;
    this->back_ = other.back_;

    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
}

// Move Assignment
template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }

    delete[] data_;

    this->data_ = rhs.data_;
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    this->front_ = rhs.front_;
    this->back_ = rhs.back_;

    rhs.data_ = nullptr;
    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.front_ = 0;
    rhs.back_ = 0;

    return *this;
}

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
    front_ = 0;
    back_ = 0;
}

template <typename T>
void ABDQ<T>::pushFront(const T& data) {
    if(size_ == capacity_) {
        resize();
    }
    front_ = (front_ - 1) % capacity_;
    data_[front_] = data;
    size_++;
}


template <typename T>
void ABDQ<T>::pushBack(const T& data) {
    if(size_ == capacity_) {
        resize();
    }
    data_[back_] = data;
    back_ = (back_ + 1) % capacity_;
    size_++;
}

template <typename T>
T ABDQ<T>::popFront() {
    if(size_ == 0) {
        throw std::runtime_error("ERROR: popFront() on empty deque.");
    }
    T result = data_[front_];
    front_ = (front_ + 1) % capacity_;
    size_--;
    return result;
}

template <typename T>
T ABDQ<T>::popBack() {
    if(size_ == 0) {
        throw std::runtime_error("ERROR: popBack() on empty deque.");
    }
    back_ = (back_ - 1) % capacity_;
    T result = data_[back_];
    size_--;
    return result;
}

template <typename T>
const T& ABDQ<T>::front() const {
    if(size_ == 0) {
        throw std::runtime_error("ERROR: front() on empty deque.");
    }
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const {
    if(size_ == 0) {
        throw std::runtime_error("ERROR: back() on empty deque.");
    }
    return data_[(back_ - 1) % capacity_];
}

template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}

template <typename T>
void ABDQ<T>::resize() {
    T* temp_array = new T[capacity_ * SCALE_FACTOR];
    for(size_t i = 0; i < size_; ++i) {
        size_t index = (front_ + i) % capacity_;
        temp_array[i] = data_[index];  
    }
    capacity_ *= SCALE_FACTOR;
    front_ = 0;
    back_ = size_;
    delete[] data_;
    data_ = temp_array;
}


