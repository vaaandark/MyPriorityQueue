#include "FibonacciHeap.h"
#include <iostream>
int main() {
    FibonacciHeap<int> h;
    h.push(1);
    std::cout << h.top() << std::endl;
    h.push(2);
    std::cout << h.top() << std::endl;
    h.push(4);
    std::cout << h.top() << std::endl;
    h.push(0);
    std::cout << h.top() << std::endl;
    h.push(-2);
    std::cout << h.top() << std::endl;
    h.pop();
    std::cout << h.top() << std::endl;
    h.pop();
    std::cout << h.top() << std::endl;
    h.pop();
    std::cout << h.top() << std::endl;
    h.pop();
    std::cout << h.top() << std::endl;
    h.pop();
    return 0;
}