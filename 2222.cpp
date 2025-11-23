#include <iostream>

int main() {
    int important_variable = 20000;
    int arr[3] = {201, 452, 893};
    
    std::cout << "До выхода за границы:" << std::endl;
    std::cout << "important_variable = " << important_variable << std::endl;
    
    arr[3] = 100000;  

    std::cout << "После выхода за границы:" << std::endl;
    std::cout << "important_variable = " << important_variable << std::endl;
    std::cout << "arr[3] = " << arr[3] << std::endl;

    arr[100000000000] = 100000000000;
    
    
    return 0;
}