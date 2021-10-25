#include <iostream>
#include <queue>
#include <vector>

#define TIMES 10000

void print_top(std::priority_queue<int, std::vector<int>, std::greater<int>> q)
{
    if (q.size() == 0) {
        std::cout << "It's an empty heap!" << std::endl;
    } else {
        std::cout << "top: " << q.top() << std::endl;
    }
}

int main()
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (int i = 0; i < TIMES; i++) {
        int cmd, num;
        std::cin >> cmd >> num;
        if (cmd == 0) {
            if (q.size()) {
                q.pop();
            }
        } else {
            q.push(num);
        }
        std::cout << "size: " << q.size() << std::endl;
        print_top(q);
    }
    return 0;
}