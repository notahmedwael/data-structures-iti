#include <iostream>
#include <stdexcept>

template <typename T>
class Array{
    private:
    int size; // index of last value in the array is size - 1
    int capacity; // the number of elements the array can hold without resizing
    T *arr;

    void resize(){
        capacity *= 2;
        T* newArr = new T[capacity];

        for (size_t i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        
        delete [] arr;
        
        arr = newArr;
    }

    public:
    Array(){
        this->size = 0;
        this->capacity = 5;
        this->arr = new T[capacity];
    }

    Array(const Array &other){
        this->size = other.getSize();
        this->capacity = other.getCapacity();

        arr = new T[capacity];

        for (int i = 0; i < size; i++)
        {
            arr[i] = other[i];
        }
    }

    void push_back(const T& val){
        if(size == capacity){
            resize();
        }
        arr[size] = val;
        size++;
    }

    void pop_back(){
        if(size == 0){
            throw std::out_of_range("Cannot pop back from empty array.");
        }

        size--;
    }

    void clear(){
        this->size = 0;
    }

    bool empty() const{
        return this->size == 0;
    }

    int getSize() const{
        return this->size;
    }

    int getCapacity() const{
        return this->capacity;
    }

    Array& operator = (const Array &other){
        if (this == &other){
            return *this;
        }
        
        delete []arr;

        this->size = other.getSize();
        this->capacity = other.getCapacity();

        arr = new T[capacity];

        for (size_t i = 0; i < size; i++)
        {
            arr[i] = other[i];
        }

        return *this;
    }


    T& operator [](int index){
        if ((0 <= index) && (index < this->size)){
            return arr[index];
        }else{
            throw std::out_of_range("Index out of bounds.");
        }
    }

    const T& operator[](int index) const{
        if ((0 <= index) && (index < this->size)){
            return arr[index];
        }else{
            throw std::out_of_range("Index out of bounds.");
        }
    }

    ~Array(){
        delete []arr;
    }
};

int main(){

    std::cout <<"Hello World" << std::endl;

    return 0;
}