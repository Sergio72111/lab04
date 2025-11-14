#include <iostream>
#include <cstdlib>

int main() {
    long long int  max = 0;
    
    for (long long int i = 5000; ; i+=1000000000){

        int* arr = (int*)malloc(i * sizeof(int));//выдялям память под массив на столько i
        
        long long int size = (i * sizeof(int)) / (1024 * 1024);//для МБ

        std::cout <<"Пытаюсь выделить "<< i  << "элементов, размером: " << size << " MB" << ' ' << size/1024 << " GB "; 
        
        if(arr == nullptr){
            std::cout << "nullptr не удалось" << "\n";
            std::cout << "\n Максимальный размер: " << max << "элементов " << (max * sizeof(int))/(1024 * 1024) << "MB" << '\n';
            break;
        }

        else{
            std::cout << arr << " Success!" << '\n';
            max = i;//макс элемент
            free(arr);//освоб памяти
        }

    }

    

    
    
    return 0;
}