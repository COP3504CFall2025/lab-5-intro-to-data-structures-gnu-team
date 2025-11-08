#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

    // Printing
    void printForward() const;
    void printReverse() const;
};

template <typename T>
ABQ<T>::ABQ() 
    : capacity_(1),
      curr_size_(0),
      array_(new T[1]) {}

template <typename T>
ABQ<T>::ABQ(const size_t capacity)
    : capacity_(capacity),
      curr_size_(0),
      array_(new T[capacity]) {}

// Copy Constructor
template <typename T>
ABQ<T>::ABQ(const ABQ& other) {
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = new T[capacity_];

    for(int i = 0; i < curr_size_; ++i) {
        this->array_[i] = other.array_[i];
    }
}

// Copy Assignment
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& rhs) {
    if(this == &rhs) {
        return *this;
    }

    //check for badalloc
    T* temp = new T[rhs.capacity_];
    for(int i = 0; i < rhs.capacity_; ++i) {
        temp[i] = rhs.array_[i];
    }

    this->curr_size_ = rhs.curr_size;
    this->capacity_ = rhs.capacity_;
    delete[] this->array_;
    this->array = temp;

    return *this;
}

template <typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept {
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = other.array_;

    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }

    delete[] this->array_;

    this->capacity_ = rhs.capacity_;
    this->curr_size_ = rhs.curr_size_;
    this->array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;

    return *this;
}

template <typename T>
ABQ<T>::~ABQ() noexcept {
    capacity_ = 0;
    curr_size_ = 0;
    delete[] array_;
    array_ = nullptr;
}

template <typename T>
size_t ABQ<T>::getSize() const noexcept {return curr_size_;};

template <typename T>
size_t ABQ<T>::getMaxCapacity() const noexcept {return capacity_;}

template <typename T>
T* ABQ<T>::getData() const noexcept {return array_;}

template <typename T>
void ABQ<T>::enqueue(const T& data) {
    if(capacity_ == curr_size_) {
        T* temp_array = new T[capacity_ * scale_factor_];
        capacity_ *= scale_factor_;
        for(std::size_t i = 0; i < curr_size_; ++i) {
            temp_array[i] = array_[i];
        }
        delete[] array_;
        array_ = temp_array;
    }

    array_[curr_size_] = data;
    curr_size_++;
}

template <typename T>
T ABQ<T>::peek() const {
    if(curr_size_ == 0) {
        throw std::runtime_error("ERROR: peek() on empty queue.");
    }
    return array_[0];
}

template <typename T>
T ABQ<T>::dequeue() {
    if(curr_size_ == 0) {
        throw std::runtime_error("ERROR: dequeue() on empty queue.");
    }

    T result = array_[0];
    curr_size_--;

    if(curr_size_ > 0  && curr_size_ == capacity_ / 4) {
        T* temp_array = new T[capacity_ / scale_factor_];
        for(std::size_t i = 0; i < curr_size_; ++i ) {
            temp_array[i] = array_[i + 1];
        }
        delete[] array_;
        array_ = temp_array;
        capacity_ /= scale_factor_;
    }
    else {
        for(std::size_t i = 0; i < curr_size_; ++i) {
            array_[i] = array_[i + 1];
        }
    }
    
    return result;
}

template <typename T>
void ABQ<T>::printForward() const {
    for(std::size_t i = 0; i < curr_size_; ++i) {
        std::cout << array_[i] << std::endl;
    }
}

template <typename T>
void ABQ<T>::printReverse() const {
    for(std::size_t i = curr_size_ - 1; i >= 0; ++i) {
        std::cout << array_[i] << std::endl;
    }
}