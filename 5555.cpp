#include<iostream>
#include <cstdlib>
#include <chrono>
#include <vector> 

int main(){
   
    //1кб = 256 элемента 
    for (int i = 1; i < 131072; i *= 2){
        auto start = std::chrono::steady_clock::now(); 
        
        int elements = i * 1024 / sizeof(int);//В КБ
        std::vector<int> arr(elements, 0);//ОБЯВА МАССИВА

        int steps =  64 * 1024 * 1024;// Произвольное количество шагов ()колво итераций, 64млн обращ к массиву
        int lenght = elements - 1;//созд маску для быстрого вычисления индекса через (i & length) вместо медленного %.

        for(int i = 0; i < steps;i++){//Много раз читаем/записываем в массив
                                //Доступ к элементам идёт по битовой маске ( & ), 
                                //что быстро позволяет получать индекс в пределах массива.
            arr[(i * 16) & lenght]++; // (x & lengthMod) равно (x % arr.Length)
        };

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout <<  i  << "KB" << ' ' << elapsed.count() << '\n';
    }

    return 0;
}
