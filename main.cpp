#include <iostream>
#include <algorithm>
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
        arr[i] = static_cast<T>(rand() % 1000);
        if (typeid(T) == typeid(float) && typeid(T) == typeid(double))
        {
            arr[i] /= 20.0;
        }
    }
}

template <typename T>
void bubblesort(T *arr, std::size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void measure_time(T *arr, std::size_t len, void (*func)(T*, std::size_t))
{
    auto start = std::chrono::high_resolution_clock::now();

    bubblesort(arr, len);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Czas wykonania: " << duration.count() << " ms" << std::endl;
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(NULL));

    size_t len = 100000;
    int arr[len];
    int* ptr = arr;

    std::cout << "Zapełniam tablicę..." << std::endl;
    populate_arr(ptr, len);
    std::cout << "Tablica zapełniona!" << std::endl;

    std::cout << "Zaczynam mierzyć czas..." << std::endl;
    measure_time(ptr, len, &bubblesort);
    std::cout << "Czas zmierzony!" << std::endl;
}