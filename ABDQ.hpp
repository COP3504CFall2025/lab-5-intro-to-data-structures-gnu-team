#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

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

};

template <typename T>
ABDQ<T>::ABDQ()
    : data_(new T[4]),
      capacity_(4),
      size_(0),
      front(0),
      back(0) {}

template <typename T>
ABDQ<T>::ABDQ(size_t capacity)
    : data_(new T[capacity]),
      capacity_(capacity),
      size_(0),
      front(0),
      back(0) {}

template <typename T>
ABDQ<T>::ABDQ(const ABDQ& other) {
    this->data_ = new T[other.capacity_];
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    this->front_ = other.front_;
    this->back_ = other.back_;

    for(int i = front_; front_ < back_; ++i) {
        this->data_[i] = other.data_[i];
    }
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ& rhs) {
    if(this == &other) {
        return *this;
    }

    T* temp_array = new T[rhs.capacity_];
    delete[] this->array_;
    this->array_ = temp_array;
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    this->front_ = rhs.front_;
    this->back_ = rhs.back_;

    for(int i = front_; front_ < back_; ++i) {
        this->data_[i] = rhs.data_[i];
    }

    return *this
}

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
void ABDQ<T>::pushFront(const T& data) {
    
}