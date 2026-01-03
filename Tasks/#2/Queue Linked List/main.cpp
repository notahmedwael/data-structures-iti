#include "../../../Implementation/DLL/DLL.hpp"
#include <iostream>

int main() {
    DLL<int> queue;

    // Enqueue elements
    queue.push_back(10);
    queue.push_back(20);
    queue.push_back(30);

    std::cout << "Initial queue: ";
    queue.traverse();

    // Front element
    std::cout << "Front element: " << queue.front() << std::endl;

    // Dequeue elements
    std::cout << "Dequeue: " << queue.pop_front() << std::endl;
    std::cout << "Dequeue: " << queue.pop_front() << std::endl;

    std::cout << "Queue after two dequeues: ";
    queue.traverse();

    // Enqueue again
    queue.push_back(40);
    queue.push_back(50);

    std::cout << "Queue after enqueueing 40 and 50: ";
    queue.traverse();

    // Dequeue all elements
    while (!queue.empty()) {
        std::cout << "Dequeue: " << queue.pop_front() << std::endl;
    }

    std::cout << "Queue empty? "
              << (queue.empty() ? "Yes" : "No")
              << std::endl;

    return 0;
}
