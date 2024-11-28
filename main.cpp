#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <typeinfo>
#include <cstddef>
#include <windows.h>

template <typename T>
void populate_arr(T *arr, std::size_t len)
{
    for (int i = 0; i < len; i++)
    {
        if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
        {
            arr[i] = static_cast<T>(rand() ) / static_cast<T> (1000 / 1.23);
        } else {
            arr[i] = static_cast<T>(rand() % 1000);
        }
    }
}

template <typename T>
void bubblesort_swap(T *arr, std::size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (arr[i] < arr[j])
            {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void bubblesort_temp(T *arr, std::size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (arr[i] < arr[j])
            {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T>
void check_if_sorted(T *arr, std::size_t len) {
    bool sorted = true;

    for (int i = 0; i < len - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            sorted = false;
        }
    }

    if (!sorted) {
        std::cout << "Uwaga! Tablica z " << len << " elementami nie posortowała się!" << std::endl;
    }
}

template <typename T>
void measure_sort_time(T, size_t len, void (*sort_func)(T*, std::size_t), int times, int* results)
{
    //std::cout << typeid(T).name() << "\t";

    for (int i = 0; i < times; i++) {
        T arr[len];
        T* arr_ptr = arr;

        populate_arr(arr_ptr, len);

        auto start = std::chrono::high_resolution_clock::now();

        sort_func(arr_ptr, len);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        check_if_sorted(arr_ptr, len);

        //results[i] = duration.count();
        std::cout << duration.count() << "\t";
        len *= 10;
    }

    std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(NULL));

    size_t len = 10;
    int times = 4;
    int types = 3;

    int results[times];
    int* ptr_results = results;

    int final_results[types][times];

    std::cout << "bubblesort ze zmienną pomocniczą" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << len << "\t";
        len *= 10;
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_temp, times, ptr_results);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_temp, times, ptr_results);
    measure_sort_time(1.11, len, &bubblesort_temp, times, ptr_results);
}