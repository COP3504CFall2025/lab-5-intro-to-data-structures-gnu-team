#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

    void print() const;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

//--------------DEFINITIONS--------------

template <typename T>
ABS<T>::ABS() 
    : capacity_(1), 
      curr_size_(0), 
      array_(new T[1]) {}

template<typename T>
ABS<T>::ABS(const size_t capacity) 
    : capacity_(capacity), 
      curr_size_(0), 
      array_(new T[capacity]) {}

// Copy Constructor
template <typename T>
ABS<T>::ABS(const ABS& other) {
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = new T[capacity_];

    for(std::size_t i = 0; i < curr_size_; ++i) {
        array_[i] = other.array_[i];
    }
}

// Copy Assignment
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS& rhs) {
    if(this == &rhs) {
        return *this;
    }
    this->capacity_ = rhs.capacity_;
    this->curr_size_ = rhs.curr_size_;

    // check for badalloc
    T* temp_array = new T[capacity_];
    delete[] this->array_;
    this->array_ = temp_array;

    for(std::size_t i = 0; i < curr_size_; ++i) {
        array_[i] = rhs.array_[i];
    }

    return *this;
}

// Copy constructor
template <typename T>
ABS<T>::ABS(ABS&& other) noexcept {
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = other.array_;

    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

// Move assignment
template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
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
}

template<typename T>
ABS<T>::~ABS() noexcept {
    capacity_ = 0;
    curr_size_ = 0;
    delete[] array_;
    array_ = nullptr;
}

template<typename T>
size_t ABS<T>::getSize() const noexcept {return curr_size_;}

template<typename T>
size_t ABS<T>::getMaxCapacity() const noexcept {return capacity_;}

template<typename T>
T* ABS<T>::getData() const noexcept {return array_;}

template<typename T>
void ABS<T>::push(const T& data) {
    if(curr_size_ == capacity_) {
        T* array_new = new T[capacity_ * scale_factor_];
        capacity_ *= scale_factor_;

        for(std::size_t i = 0; i < curr_size_; ++i) {
            array_new[i] = array_[i];
        }
        
        delete[] array_;
        array_ = array_new;
    }
    array_[curr_size_] = data;
    curr_size_++;
} 

template <typename T>
T ABS<T>::peek() const {
    if(curr_size_ > 0) {
        return array_[curr_size_ - 1];
    } 
    else {
        throw std::runtime_error("ERROR: peek() on stack with no elements");
    }
}

template <typename T>
T ABS<T>::pop() {
    if(curr_size_ > 0) {
        curr_size_--;
        return array_[curr_size_];
    } 
    else {
        throw std::runtime_error("ERROR: pop() on stack with no elements");
    }
}