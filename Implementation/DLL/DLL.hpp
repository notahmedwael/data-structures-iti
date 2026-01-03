#ifndef DLL_HPP
#define DLL_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class DLL{
private:
    struct Node {
        T val;
        Node* next;
        Node* prev;
        Node(const T& val) : val(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DLL(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DLL(){
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const T& val){
        Node* newNode = new Node(val);
        if(empty()){
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void push_front(const T& val){
        Node* newNode = new Node(val);
        if(empty()){
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAt(const T& val, const int index){
        if(index < 0 || index > size){
            throw std::out_of_range("Index out of range");
        }

        if(index == 0){
            push_front(val);
            return;
        }

        if (index == size){
            push_back(val);
            return;
        }

        Node* curr = head;
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }

        Node* newNode = new Node(val);
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;

        size++;
    }

    void insertBefore(const T& queryVal, const T& toBeInsertedVal){
        Node* curr = head;

        while(curr != nullptr && curr->val != queryVal){
            curr = curr->next;
        }

        if(curr == nullptr){
            throw std::out_of_range("Element not in range.");
        }

        if (curr == head){
            push_front(toBeInsertedVal);
            return;
        }

        Node* newNode = new Node(toBeInsertedVal);
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;

        size++;
    }

    void insertAfter(const T& queryVal, const T& toBeInsertedVal){
        Node* curr = head;

        while(curr != nullptr && curr->val != queryVal){
            curr = curr->next;
        }

        if(curr == nullptr){
            throw std::out_of_range("Element not in range.");
        }

        if (curr == tail){
            push_back(toBeInsertedVal);
            return;
        }

        Node* newNode = new Node(toBeInsertedVal);
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next->prev = newNode;
        curr->next = newNode;

        size++;
    }

    T getDataByIndex(const int index){
        if(index < 0 || index >= size){
            throw std::out_of_range("Index out of bounds");
        }

        Node* curr = head;
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }
        return curr->val;
    }

    void removeElement(const T& element){
        Node* curr = head;

        while(curr != nullptr){
            if(curr->val == element){
                if(curr == head && curr == tail){
                    head = nullptr;
                    tail = nullptr;
                } else if(curr == head){
                    curr->next->prev = nullptr;
                    head = head->next;
                } else if(curr == tail){
                    curr->prev->next = nullptr;
                    tail = tail->prev;
                } else{
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr;
                size--;
                return;
            }
            curr = curr->next;
        }
    }

    void removeElementAll(const T& element){
        Node* curr = head;

        while(curr != nullptr){
            if(curr->val == element){
                if(curr == head && curr == tail){
                    head = nullptr;
                    tail = nullptr;
                } else if(curr == head){
                    curr->next->prev = nullptr;
                    head = head->next;
                } else if(curr == tail){
                    curr->prev->next = nullptr;
                    tail = tail->prev;
                } else{
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                Node* nextNode = curr->next;
                delete curr;
                size--;
                curr = nextNode;
            } else {
                curr = curr->next;
            }
        }
    }

    void removeAt(const int index){
        if(index < 0 || index >= size){
            throw std::out_of_range("Can't remove an element out of bounds");
        }

        Node* curr = head;
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }

        if(curr == head && curr == tail){
            head = nullptr;
            tail = nullptr;
        } else if(curr == head){
            curr->next->prev = nullptr;
            head = head->next;
        } else if(curr == tail){
            curr->prev->next = nullptr;
            tail = tail->prev;
        } else{
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        delete curr;
        size--;
    }

    void traverse() const{
        Node* curr = head;
        while(curr != nullptr){
            std::cout << "<=> " << curr->val << " <=> ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    void traverseReverse() const{
        Node* curr = tail;
        while(curr != nullptr){
            std::cout << "<=> " << curr->val << " <=> ";
            curr = curr->prev;
        }
        std::cout << std::endl;
    }

    T pop_back(){
        if(empty()){
            throw std::out_of_range("Cannot pop back from an empty list");
        }

        Node* curr = tail;
        T currentVal = curr->val;

        tail = tail->prev;
        if(tail){
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete curr;
        size--;
        return currentVal;
    }

    T pop_front(){
        if(empty()){
            throw std::out_of_range("Cannot pop front from an empty list");
        }

        Node* curr = head;
        T currentVal = curr->val;

        head = head->next;
        if(head){
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete curr;
        size--;
        return currentVal;
    }

    T& front(){
        if(empty()){
            throw std::out_of_range("Cannot return the front of an empty list");
        }
        return head->val;
    }

    T& back(){
        if(empty()){
            throw std::out_of_range("Cannot return the back of an empty list");
        }
        return tail->val;
    }

    bool empty() const{
        return size == 0;
    }

    int getSize() const{
        return size;
    }

    T& operator[](int index){
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        Node* curr = head;
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }

        return curr->val;
    }

    const T& operator[](int index) const{
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        Node* curr = head;
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }

        return curr->val;
    }
};

#endif
