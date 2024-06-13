#include <iostream>

auto makeCounter(int defaultValue = 0) {
    int counter = defaultValue;
    return [=]() mutable {
        return counter++;
    };
}

int main()
{
    
    auto Counter1 = makeCounter();
    std::cout << Counter1() << std::endl;
    std::cout << Counter1() << std::endl;
    auto Counter2 = makeCounter(12);
    std::cout << Counter2() << std::endl;
    std::cout << Counter2() << std::endl;
    std::cout << Counter2() << std::endl;
    system("pause");
}


