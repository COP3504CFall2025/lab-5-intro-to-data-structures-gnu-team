#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T datum;
		Node* next;
		Node* prev;
	};

	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node* getHead();
	const Node* getHead() const;
	Node* getTail();
	const Node* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};

//---------------DEFINITIONS-------------------------

template <typename T>
void LinkedList<T>::printForward() const {
    Node* next = head;
    while(next != nullptr) {
        std::cout << next->datum << std::endl;
        next = next->next;
    }
}

template <typename T>
void LinkedList<T>::printReverse() const {
    Node* prev = tail;
    while(prev != nullptr) {
        std::cout << prev->datum << std::endl;
        prev = prev->next;
    }
}

template <typename T>
unsigned int LinkedList<T>::getCount() const {
    return count;
}

template <typename T>
LinkedList<T>::Node* LinkedList<T>::getHead() {
    return head;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getTail() const {
    return tail;
}

template <typename T>
void LinkedList<T>::addHead(const T& data) {
    Node* current = new Node {data, nullptr, nullptr};

    if(head == nullptr) {
        head = current;
        tail = current;

    }
    else {
        current->next = head;
        head->prev = current;
        head = current;
    }
    count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
    Node* current = new Node {data, nullptr, nullptr};

    if(tail == nullptr) {
        head = current;
        tail = current;
    }
    else {
        current->prev = tail;
        tail->next = current;
        tail = current;
    }
    count++;
}

template <typename T>
bool LinkedList<T>::removeHead() {
    // Empty List
    if(head == nullptr ) {
        return false;
    }
    // List has one element
    else if(head->next == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    // List has multiple elements
    else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    
    count--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
    // Empty List
    if(tail == nullptr ) {
        return false;
    }
    // List has one element
    else if(tail->prev == nullptr) {
        delete prev;
        tail = nullptr;
        head = nullptr;
    }
    // List has multiple elements
    else {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
    
    count--;
    return true;
}

template <typename T>
void LinkedList<T>::Clear() {
    while(count > 0) {
        removeHead();
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if(this == &other) {
        return *this;
    }

    Clear();
    
    this->head = other.head;
    this->tail = other.tail;
    this->count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = nullptr.
    
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if(this == &other) {
        return *this;
    }

    Clear();

    Node* current = other.getHead()
    while(current != nullptr) {
        addTail(current->data);
        current = current->next;
    }
    
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
    Node* current = other.getHead()
    while(current != nullptr) {
        addTail(current->data);
        current = current->next;
    }
    
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
    this->head = other.head;
    this->tail = other.tail;
    this->count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = nullptr.
    
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}



