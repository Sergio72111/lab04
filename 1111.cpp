#include <iostream>
#include <cstdlib>   // malloc, free
#include <new>       // std::bad_alloc

int main() {

    setlocale(LC_ALL, "RUS");

    for (unsigned int i = 10; ; i += 100000000) {

        try {

            // Выделение памяти через malloc
            unsigned int* ptr = (unsigned int*)malloc(i * sizeof(unsigned int));

            // Если malloc вернул NULL — бросаем исключение
            if (!ptr) {
                throw std::bad_alloc();
            }

            long long int size_bytes = i * static_cast<long long int>(sizeof(unsigned int));
            double size_mb = static_cast<double>(size_bytes) / (1024.0 * 1024.0);
            double size_gb = size_mb / 1024.0;

            std::cout << "Элементов: " << i
                << " Размер: " << size_gb << " GB"
                << " (" << size_mb << " MB)" << std::endl;

            // Освобождаем память
            free(ptr);
        }

        catch (const std::bad_alloc& fals) {
            std::cerr << "Ошибка выделения памяти: " << fals.what();
            break;
        }
    }

    return 0;
}
