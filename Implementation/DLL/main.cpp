#include <iostream>
#include <stdexcept>

template <typename T>
class DLL{
    private:
    struct Node
    {
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

        if (index == size - 1){
            push_back(val);
            return;
        }

        Node* curr = head;
        for (size_t i = 1; i < index - 1; i++)
        {
            curr = curr->next;
        }

        Node* newNode = new Node(val);

        // Link newNode between curr->prev and curr
        newNode->next = curr;
        newNode->prev = curr->prev;

        curr->prev->next = newNode;
        curr->prev = newNode;

        size++;
        
    }

    void insertBefore(const T& queryVal, const T& toBeInsertedVal){

    }

    void insertAfter(const T& queryVal, const T& toBeInsertedVal){

    }

    T getDataByIndex(const int index){

        if(index < 0 || index >= size){
            throw std::out_of_range("Index out of bounds")
        }

        Node* curr = head;

        for (size_t i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        T currentVal = curr->val;

        return currentVal;
    }

    void removeElement(T& element){
    }

    void removeElementAll(T& element){

    }

    void traverse() const{
        Node* curr = head;

        while(curr != nullptr){
            std::cout << "<=> " << curr->val << " <=> ";
            curr = curr->next;
        }
        cout << endl;
    }

    void traverseReverse() const{
        Node* curr = tail;

        while(curr != nullptr){
            std::cout << "<=> " << curr->val << " <=> ";
            curr = curr->prev;
        }

        cout << endl;
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
            head = nullptr; // List had one element
        }

        delete curr;
        size --;

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
            tail = nullptr; // List had one element
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
};

int main(){
    return 0;
}