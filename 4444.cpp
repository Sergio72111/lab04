#include <iostream>

int main() {

    int* a = new int[10]; // память выделили
    int* b = new int[10]; // и здесь тоже

    for(int i = 0; i < 10; i++) {
        a[i] = i;//0 1 2 3 4 [5]  67 8 9 10
        b[i] = i * 2;//0 2 4 5 8 [10]
    }

    std::cout << a[5] + b[5] << std::endl;

    // delete[] a;
    // delete[] b;
    // Эти строки не выполнены → утечка

    return 0;
}
