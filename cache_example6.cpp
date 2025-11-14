#define HAVE_STRUCT_TIMESPEC
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h> 

////////////////////////////////////////////
// Демонстрация false sharing (ложного совместного использования кэш-линий)
////////////////////////////////////////////
// Мы запускаем N_THREADS потоков, каждый из которых будет изменять массив "res".
// Если потоки изменяют элементы на одной и той же кэш-линии (offset=0) => будет медленно из-за false sharing.
// Если каждый поток изменяет элементы на разных кэш-линиях (offset=16, так как res содержит int, а кэш-линия 64 байта) => быстрее.

struct s_thread_params
{
    // Структура параметров для потока
    int thread_id;  // идентификатор потока
    int pos;        // индекс элемента массива res, который будет изменять поток
    int* res;       // указатель на массив, общий для всех потоков
};

void* worker_routine(void* params) {
    // Функция, которую выполняет каждый поток
    int i;

    // Приводим указатель params к нашей структуре параметров
    struct s_thread_params* p = (struct s_thread_params*)params;

    // Каждый поток 100000000 раз увеличивает свой элемент массива
    for (i = 0; i < 100000000; i++) {
        p->res[p->pos] += 1;  // инкремент конкретного элемента массива
    }

    printf("thread %d done\n", p->thread_id);  // вывод, что поток завершён

    return NULL;
}

int main(int argc, char* argv[])
{
    int nt;
    int N_THREADS = 4;  // количество потоков
    // Выделяем массив int для результатов. Умножаем на 16, чтобы можно было изменять offset
    int* res = (int*)malloc(N_THREADS * 16 * sizeof(int));
    int offset;

    // Создаём массив структур параметров для потоков
    struct s_thread_params* p_thread_params = (s_thread_params*)malloc(N_THREADS * sizeof(struct s_thread_params));
    // Создаём массив идентификаторов потоков
    pthread_t* worker = (pthread_t*)malloc(N_THREADS * sizeof(pthread_t));

    // Цикл по смещению offset: проверяем 0 (false sharing) и 16 (разные кэш-линии)
    for (offset = 0; offset <= 16; offset += 16) {

        // Настройка каждого потока
        for (nt = 0; nt < N_THREADS; nt++) {

            p_thread_params[nt].thread_id = nt;  // id потока
            p_thread_params[nt].res = res;       // общий массив
            p_thread_params[nt].pos = nt * offset; // индекс для этого потока с заданным offset

            // Создаём поток и запускаем его выполнение
            pthread_create(&worker[nt], NULL, worker_routine, (void*)&p_thread_params[nt]);
            printf("thread %d started\n", nt);
        }

        // Засекаем время выполнения всех потоков
        int64_t t0 = clock();
        // Ждём завершения всех потоков
        for (nt = 0; nt < N_THREADS; nt++) {
            pthread_join(worker[nt], NULL);
        }
        // Вывод времени работы для данного offset
        printf("offset: %d time: %" PRId64 "ms\n", offset, clock() - t0);
    }

    // Освобождение динамически выделенной памяти
    free(worker);
    free(p_thread_params);
    free(res);

    return 0;
}
