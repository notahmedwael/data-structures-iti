#include <iostream>

#include "../../../Implementation/DLL/DLL.hpp"


int main() {
    DLL<int> dll;

    dll.push_back(10);
    dll.push_back(20);
    dll.push_front(5);
    dll.traverse();

    dll.insertAt(15, 2);
    dll.traverse();

    dll.insertBefore(15, 12);
    dll.insertAfter(15, 18);
    dll.traverse();

    std::cout << "Index 2: " << dll[2] << std::endl;
    dll[2] = 100;
    dll.traverse();

    std::cout << "Front: " << dll.front() << std::endl;
    std::cout << "Back: " << dll.back() << std::endl;

    dll.removeElement(15);
    dll.traverse();

    dll.push_back(20);
    dll.push_back(20);
    dll.removeElementAll(20);
    dll.traverse();

    dll.removeAt(1);
    dll.traverse();

    dll.traverseReverse();

    std::cout << "Size: " << dll.getSize() << std::endl;

    return 0;
}
