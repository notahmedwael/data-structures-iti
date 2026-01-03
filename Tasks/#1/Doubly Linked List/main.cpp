#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;

        Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    bool isEmpty() const {
        return length == 0;
    }

    int size() const {
        return length;
    }

    void insertAtBegin(const T& element) {
        Node* newNode = new Node(element);

        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    void insertAtEnd(const T& element) {
        Node* newNode = new Node(element);

        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void insertAtPos(int pos, const T& element) {
        if (pos < 0 || pos > length) {
            cout << "Out of range." << endl;
            return;
        }

        if (pos == 0) {
            insertAtBegin(element);
            return;
        }

        if (pos == length) {
            insertAtEnd(element);
            return;
        }

        Node* current = head;
        for (int i = 1; i < pos; i++) {
            current = current->next;
        }

        Node* newNode = new Node(element);
        newNode->next = current;
        newNode->prev = current->prev;

        current->prev->next = newNode;
        current->next = newNode;

        length++;
    }

    void removeFirst() {
        if (isEmpty()) {
            cout << "Empty list." << endl;
            return;
        }

        Node* temp = head;

        if (length == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        length--;
    }

    void removeLast() {
        if (isEmpty()) {
            cout << "Empty list." << endl;
            return;
        }

        Node* temp = tail;

        if (length == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        length--;
    }

    void pop(){
        removeLast();
    }

    void removeElement(const T& element) {
        if (isEmpty()) {
            cout << "List empty." << endl;
            return;
        }

        Node* current = head;

        while (current != nullptr && current->value != element) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Element not found." << endl;
            return;
        }

        if (current == head) {
            removeFirst();
        } else if (current == tail) {
            removeLast();
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
        }
    }

    void removePos(int pos) {
        if (pos < 0 || pos >= length) {
            cout << "Invalid position." << endl;
            return;
        }

        if (pos == 0) {
            removeFirst();
            return;
        }

        if (pos == length - 1) {
            removeLast();
            return;
        }

        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        length--;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printReverse() const {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        length = 0;
    }
};
