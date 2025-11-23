#include <iostream>

int main() {
    
    int a = 1111, b = 2222;
    int arr[3] = {100, 200, 300}; 

    // *(ptr + 6) = 1111
    // *(ptr + 7) = 1111
    // *(ptr + 8) = 1111

    int *ptr = arr;
    std::cout << "До *(ptr + 6) = " << *(ptr + 6);   
    *(ptr + 6) = 600; 
    std::cout << " После *(ptr + 6) = " << *(ptr + 6);
    // на 97 исключение

    *(ptr + 1000000000000000) = 100000000000000000000000;

    return 0;
}